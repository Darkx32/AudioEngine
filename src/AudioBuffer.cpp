#include <AudioEngine/AudioBuffer.hpp>
#include <AudioEngine/tools.hpp>
#include <AL/al.h>
#include <string>
extern "C"
{
    #include <libavformat/avformat.h>
    #include <libavcodec/avcodec.h>
    #include <libavutil/opt.h>
    #include <libswresample/swresample.h>
}

namespace AudioEngine
{
    /**
     * Create a Audio Buffer
     * @param file path to audio file
     */
    AudioBuffer::AudioBuffer(const std::string& file) : mNumChannels(0), mSampleRate(0), mBitsPerSample(0), mAudioStreamIndex(0), mFormat(0), mBuffer(0)
    {
        std::string msg = "Loading file " + file;
        logger(msg.c_str());

        // Start format context
        AVFormatContext* formatContext = nullptr;
        if (avformat_open_input(&formatContext, file.c_str(), nullptr, nullptr))
        {
            logger("Error to open format context", LOG_ERROR);
            return;
        }
        if (avformat_find_stream_info(formatContext, nullptr) > 0)
        {
            logger("File not contains nothing", LOG_ERROR);
            avformat_close_input(&formatContext);
            return;
        }

        // Get index of audio stream in codecpar
        mAudioStreamIndex = -1;
        for (unsigned int i = 0; i < formatContext->nb_streams; i++) {
            if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
                mAudioStreamIndex = static_cast<int>(i);
            }
        }
    
        if (mAudioStreamIndex == -1) {
            logger("Error not found a audio in file", LOG_ERROR);
            avformat_close_input(&formatContext);
            return;
        }

        // Find decoder
        AVCodecParameters* codecParameters = formatContext->streams[mAudioStreamIndex]->codecpar;
        const AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);
        if (!codec)
        {
            logger("Not found any codec in audio file", LOG_ERROR);
            avformat_close_input(&formatContext);
            return;
        }

        // Alloc codec context
        AVCodecContext* codecContext = avcodec_alloc_context3(codec);
        if (!codecContext)
        {
            logger("Error to alloc codec context", LOG_ERROR);
            avformat_close_input(&formatContext);
            return;
        }

        if (avcodec_parameters_to_context(codecContext, codecParameters) < 0)
        {
            logger("Error when copying parameters to codec context", LOG_ERROR);
            avformat_close_input(&formatContext);
            avcodec_free_context(&codecContext);
            return;
        }

        // Open codec context
        if (avcodec_open2(codecContext, codec, nullptr) < 0)
        {
            logger("Error to open codec context", LOG_ERROR);
            avformat_close_input(&formatContext);
            avcodec_free_context(&codecContext);
            return;
        }

        this->getDetailsFromAudio(formatContext, codecContext, codecParameters);
        this->generateBufferData(formatContext, codecContext);

        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);

        genBufferData();
    }

    AudioBuffer::~AudioBuffer() {
        alDeleteBuffers(1, &mBuffer);
        mData.clear();
    }

    /**
     * Get number of channels
     * @return Number of channels
     */
    int AudioBuffer::getNumChannels() const
    {
        return mNumChannels;
    }

    /**
     * Get sample rate from audio file
     * @return Sample rate
     */
    int AudioBuffer::getSampleRate() const
    {
        return mSampleRate;
    }

    /**
     * Get bits per sample from audio file
     * @return Bits per sample
     */
    short AudioBuffer::getBitsPerSample() const
    {
        return mBitsPerSample;
    }

    /**
     * Get audio data in vector that contains bytes
     * @return Vector with bytes
     */
    std::vector<uint8_t> AudioBuffer::getBufferData()
    {
        return mData;
    }

    unsigned int& AudioBuffer::getBuffer() {
        return mBuffer;
    }

    /**
     * Get audio file details and save it in variables on class
     * @param fc AVFormatContext
     * @param cc AVCodecContext
     * @param cp AVCodecParameters
     */
    void AudioBuffer::getDetailsFromAudio(void* fc, void* cc, void* cp)
    {
        AVFormatContext* formatContext = static_cast<AVFormatContext*>(fc);
        AVCodecContext* codecContext = static_cast<AVCodecContext*>(cc);
        AVCodecParameters* codecParameters = static_cast<AVCodecParameters*>(cp);

        AVPacket packet;
        AVFrame* frame = av_frame_alloc();
        if (!frame)
        {
            logger("Error to aloc frame", LOG_ERROR);
            avformat_close_input(&formatContext);
            avcodec_free_context(&codecContext);
            return;
        }

        while (av_read_frame(formatContext, &packet) >= 0)
        {
            if (packet.stream_index == mAudioStreamIndex)
            {
                if (avcodec_send_packet(codecContext, &packet) == 0)
                {
                    if (avcodec_receive_frame(codecContext, frame) == 0)
                    {
                        this->mBitsPerSample = static_cast<short>(av_get_bytes_per_sample(codecContext->sample_fmt) * 8);
                        break;
                    }
                }
            }
            av_packet_unref(&packet);
        }

        this->mNumChannels = codecParameters->ch_layout.nb_channels;
        this->mSampleRate = codecParameters->sample_rate;

        logger("Audio is loaded");
        std::string msg = "Number of channels: " + std::to_string(this->mNumChannels) + " Sample rate: " + 
            std::to_string(this->mSampleRate) + " Bits per sample: " + std::to_string(this->mBitsPerSample);
        logger(msg.c_str());

        av_frame_free(&frame);
    }

    /**
     * Generate audio buffer to play
     * @param fc AVFormatContext
     * @param cc AVCodecContext
     */
    void AudioBuffer::generateBufferData(void* fc, void* cc)
    {
        AVFormatContext* formatContext = static_cast<AVFormatContext*>(fc);
        AVCodecContext* codecContext = static_cast<AVCodecContext*>(cc);

        const AVSampleFormat out_format = (codecContext->sample_fmt == AV_SAMPLE_FMT_U8) ? codecContext->sample_fmt : AV_SAMPLE_FMT_S16;

        SwrContext* swrContext = swr_alloc();
        av_opt_set_chlayout(swrContext, "in_chlayout", &formatContext->streams[0]->codecpar->ch_layout, 0);
        av_opt_set_int(swrContext, "in_sample_rate", this->mSampleRate, 0);
        av_opt_set_sample_fmt(swrContext, "in_sample_fmt", codecContext->sample_fmt, 0);
        av_opt_set_chlayout(swrContext, "out_chlayout", &formatContext->streams[0]->codecpar->ch_layout, 0);
        av_opt_set_int(swrContext, "out_sample_rate", this->mSampleRate, 0);
        av_opt_set_sample_fmt(swrContext, "out_sample_fmt", out_format, 0);
        if (swr_init(swrContext) < 0)
        {
            logger("Error to init swrContext", LOG_ERROR);
            return;
        }
        
        AVPacket pkt;
        AVFrame* frame = av_frame_alloc();
        while (av_read_frame(formatContext, &pkt) >= 0)
        {
            if (pkt.stream_index == mAudioStreamIndex)
            {
                if (avcodec_send_packet(codecContext, &pkt) == 0)
                {
                    while (avcodec_receive_frame(codecContext, frame) == 0)
                    {   
                        uint8_t** output = nullptr;
                        av_samples_alloc_array_and_samples(&output, nullptr, this->mNumChannels, frame->nb_samples, codecContext->sample_fmt, 0);
                        swr_convert(swrContext, output, frame->nb_samples, frame->data, frame->nb_samples);

                        const int new_data_size = av_samples_get_buffer_size(nullptr, this->mNumChannels, frame->nb_samples, out_format, 0);

                        mData.insert(mData.end(), output[0], output[0] + new_data_size);

                        av_freep((void*)&output[0]);
                        av_freep((void*)&output);
                    }
                }
            }
            av_packet_unref(&pkt);
        }

        av_frame_free(&frame);
        swr_free(&swrContext);
    }

    /**
     * Generate the buffer data
     * @param buffer OpenAL Buffer (is NULL)
     * @param audioBuffer audioBuffer
     * @param format audio format
     */
    void AudioBuffer::genBufferData()
    {
        ALuint error;
        alGenBuffers(1, &mBuffer);
        hasOpenALError(&error);

        if (mBitsPerSample == 8)
        {
            if (mNumChannels == 1)
                mFormat = AL_FORMAT_MONO8;
            else if (mNumChannels == 2)
                mFormat = AL_FORMAT_STEREO8;
        }
        else
        {
            if (mNumChannels == 1)
                mFormat = AL_FORMAT_MONO16;
            else if (mNumChannels == 2)
                mFormat = AL_FORMAT_STEREO16;
        }


        alBufferData(mBuffer, (ALenum)mFormat, mData.data(), static_cast<ALsizei>(mData.size()), mSampleRate);
        hasOpenALError(&error);
    }
}