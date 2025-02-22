#include <AudioBuffer.h>
#include "tools.h"
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
    AudioBuffer::AudioBuffer(std::string file)
    {
        std::string msg = "Loading file " + file;
        logger(msg.c_str());

        AVFormatContext* formatContext = nullptr;
        if (avformat_open_input(&formatContext, file.c_str(), nullptr, nullptr))
        {
            logger("Error to open format context", LOG_ERROR);
            exit(1);
        }
        if (avformat_find_stream_info(formatContext, nullptr) > 0)
        {
            logger("File not contains nothing", LOG_ERROR);
            avformat_close_input(&formatContext);
            exit(1);
        }

        this->audioStreamIndex = -1;
        for (int i = 0; i < formatContext->nb_streams; i++) {
            if (formatContext->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
                audioStreamIndex = i;
            }
        }
    
        if (audioStreamIndex == -1) {
            logger("Error not found a audio in file", LOG_ERROR);
            avformat_close_input(&formatContext);
            exit(1);
        }

        AVCodecParameters* codecParameters = formatContext->streams[audioStreamIndex]->codecpar;
        const AVCodec* codec = avcodec_find_decoder(codecParameters->codec_id);
        if (!codec)
        {
            logger("Not found any codec in audio file", LOG_ERROR);
            avformat_close_input(&formatContext);
            exit(1);
        }

        AVCodecContext* codecContext = avcodec_alloc_context3(codec);
        if (!codecContext)
        {
            logger("Error to alloc codec context", LOG_ERROR);
            avformat_close_input(&formatContext);
            exit(1);
        }

        if (avcodec_parameters_to_context(codecContext, codecParameters) < 0)
        {
            logger("Error when copying parameters to codec context", LOG_ERROR);
            avformat_close_input(&formatContext);
            avcodec_free_context(&codecContext);
            exit(1);
        }

        if (avcodec_open2(codecContext, codec, nullptr) < 0)
        {
            logger("Error to open codec context", LOG_ERROR);
            avformat_close_input(&formatContext);
            avcodec_free_context(&codecContext);
            exit(1);
        }

        this->getDetailsFromAudio(formatContext, codecContext, codecParameters);
        this->generateBufferData(formatContext, codecContext);

        avcodec_free_context(&codecContext);
        avformat_close_input(&formatContext);
    }

    short AudioBuffer::getNumChannels()
    {
        return this->numChannels;
    }

    int AudioBuffer::getSampleRate()
    {
        return this->sampleRate;
    }

    std::vector<uint8_t> AudioBuffer::getBufferData()
    {
        return this->data;
    }

    short AudioBuffer::getBitsPerSample()
    {
        return this->bitsPerSample;
    }

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
            exit(1);
        }

        while (av_read_frame(formatContext, &packet) >= 0)
        {
            if (packet.stream_index == audioStreamIndex)
            {
                if (avcodec_send_packet(codecContext, &packet) == 0)
                {
                    if (avcodec_receive_frame(codecContext, frame) == 0)
                    {
                        this->bitsPerSample = av_get_bytes_per_sample(codecContext->sample_fmt) * 8;
                        break;
                    }
                }
            }
            av_packet_unref(&packet);
        }

        this->numChannels = codecParameters->ch_layout.nb_channels;
        this->sampleRate = codecParameters->sample_rate;

        logger("Audio is loaded");
        std::string msg = "Number of channels: " + std::to_string(this->numChannels) + " Sample rate: " + 
            std::to_string(this->sampleRate) + " Bits per sample: " + std::to_string(this->bitsPerSample);
        logger(msg.c_str());

        av_frame_free(&frame);
    }

    void AudioBuffer::generateBufferData(void* fc, void* cc)
    {
        AVFormatContext* formatContext = static_cast<AVFormatContext*>(fc);
        AVCodecContext* codecContext = static_cast<AVCodecContext*>(cc);

        AVSampleFormat out_format = (codecContext->sample_fmt == AV_SAMPLE_FMT_U8) ? codecContext->sample_fmt : AV_SAMPLE_FMT_S16;

        SwrContext* swrContext = swr_alloc();
        av_opt_set_chlayout(swrContext, "in_chlayout", &formatContext->streams[0]->codecpar->ch_layout, 0);
        av_opt_set_int(swrContext, "in_sample_rate", this->sampleRate, 0);
        av_opt_set_sample_fmt(swrContext, "in_sample_fmt", codecContext->sample_fmt, 0);
        av_opt_set_chlayout(swrContext, "out_chlayout", &formatContext->streams[0]->codecpar->ch_layout, 0);
        av_opt_set_int(swrContext, "out_sample_rate", this->sampleRate, 0);
        av_opt_set_sample_fmt(swrContext, "out_sample_fmt", out_format, 0);
        if (swr_init(swrContext) < 0)
        {
            logger("Error to init swrContext", LOG_ERROR);
            exit(1);
        }
        
        AVPacket pkt;
        AVFrame* frame = av_frame_alloc();
        while (av_read_frame(formatContext, &pkt) >= 0)
        {
            if (pkt.stream_index == audioStreamIndex)
            {
                if (avcodec_send_packet(codecContext, &pkt) == 0)
                {
                    while (avcodec_receive_frame(codecContext, frame) == 0)
                    {   
                        uint8_t** output = nullptr;
                        av_samples_alloc_array_and_samples(&output, nullptr, this->numChannels, frame->nb_samples, codecContext->sample_fmt, 0);
                        swr_convert(swrContext, output, frame->nb_samples, (const uint8_t**)frame->data, frame->nb_samples);

                        int new_data_size = av_samples_get_buffer_size(nullptr, this->numChannels, frame->nb_samples, out_format, 0);

                        data.insert(data.end(), output[0], output[0] + new_data_size);

                        av_freep(&output[0]);
                        av_freep(&output);
                    }
                }
            }
            av_packet_unref(&pkt);
        }

        av_frame_free(&frame);
        swr_free(&swrContext);
    }
}