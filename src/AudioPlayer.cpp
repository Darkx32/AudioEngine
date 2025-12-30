#include <AudioEngine/AudioPlayer.hpp>
#include <AudioEngine/tools.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <algorithm>
extern "C"
{
    #include <libavfilter/avfilter.h>
}


namespace AudioEngine
{
    /**
     * Create a new AudioPlayer
     */
    AudioPlayer::AudioPlayer()
    {
        av_log_set_level(AV_LOG_QUIET);
        ALCdevice* device = alcOpenDevice(nullptr);
        if (!device)
        {
            logger(LOG_ERROR, "Error to open default device");
            exit(1);
        }
        ALCcontext* context = alcCreateContext(device, nullptr);
        if (!context)
        {
            logger(LOG_ERROR, "Error to create OpenAL Context");
            exit(1);
        }
        alcMakeContextCurrent(context);

        isPlayingAudio = true;
    }

    AudioPlayer::~AudioPlayer()
    {
        this->streams.clear();
    }

    /**
     * Update swaps of the player
     */
    void AudioPlayer::updateSwaps()
    {
        ALenum error, state;
        if ((error = alGetError()) != AL_NO_ERROR)
            logger(LOG_ERROR, getErrorByOpenAL(error));

        isPlayingAudio = false;

        for(const auto stream : this->streams)
        {
            alGetSourcei(*stream, AL_SOURCE_STATE, &state);
            if (state == AL_PLAYING) 
            {
                this->isPlayingAudio = true;
                break;
            }
        }
    }

    /**
     * Check if audio is running
     * @return True if audio is running
     */
    bool AudioPlayer::isRunningAudio() const
    {
        return this->isPlayingAudio;
    }
    
    /**
     * Play a stream and save it to internal controller
     * @param audioStream Stream to be played
     */
    void AudioPlayer::playStream(unsigned int* audioStream)
    {
        if (std::find(streams.begin(), streams.end(), audioStream) != streams.end())
            logger(LOG_WARN, "Stream already added");
        else {
            this->streams.push_back(audioStream);
            alSourcePlay(*audioStream);
        }
    }

    /**
     * Pause a stream
     * @param audioStream Stream to be paused
     */
    void AudioPlayer::pauseStream(const unsigned int* audioStream)
    {
        if (std::find(streams.begin(), streams.end(), audioStream) != streams.end())
            alSourcePause(*audioStream);
        else
            logger(LOG_WARN, "Stream not added");
    }

    /**
     * Stop a stream
     * @param audioStream Stream to be stopped
     */
    void AudioPlayer::stopStream(const unsigned int* audioStream)
    {
        if (std::find(streams.begin(), streams.end(), audioStream) != streams.end())
            alSourceStop(*audioStream);
        else
            logger(LOG_WARN, "Stream not added");
    }

    /**
     * set volume of every streams in player
     * @param volume Volume to be set 0%-100%
     */
    void AudioPlayer::setGeneralVolume(const unsigned int volume) const
    {
        for(const unsigned int *stream : this->streams)
        {
            alSourcef(*stream, AL_GAIN, (float)volume / 100.0f);
        }
    }
}