#include <AudioEngine/AudioPlayer.hpp>
#include <AudioEngine/tools.hpp>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
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
        ALCdevice* device = alcOpenDevice(NULL);
        if (!device)
        {
            logger("Error to open default device", LOG_ERROR);
            exit(1);
        }
        ALCcontext* context = alcCreateContext(device, NULL);
        if (!context)
        {
            logger("Error to create OpenAL Context", LOG_ERROR);
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
     * Add a stream to the player
     * @param audioStream Stream to be added
     */
    void AudioPlayer::addStream(unsigned int* audioStream)
    {
        if (std::find(streams.begin(), streams.end(), audioStream) != streams.end())
            logger("Stream already added", LOG_WARN);
        else
            this->streams.push_back(audioStream);
    }

    /**
     * Update swaps of the player
     */
    void AudioPlayer::updateSwaps()
    {
        ALenum error, state;
        if ((error = alGetError()) != AL_NO_ERROR)
            logger(getErrorByOpenAL(error), LOG_ERROR);

        isPlayingAudio = false;

        for(unsigned int* stream : this->streams)
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
    bool AudioPlayer::isRunningAudio()
    {
        return this->isPlayingAudio;
    }
    
    /**
     * Play a stream
     * @param audioStream Stream to be played
     */
    void AudioPlayer::playStream(unsigned int* source)
    {
        alSourcePlay(*source);
    }

    /**
     * Pause a stream
     * @param audioStream Stream to be paused
     */
    void AudioPlayer::pauseStream(unsigned int* audioStream)
    {
        if (std::find(streams.begin(), streams.end(), audioStream) != streams.end())
            alSourcePause(*audioStream);
        else
            logger("Stream not added", LOG_ERROR);
    }

    /**
     * Stop a stream
     * @param audioStream Stream to be stopped
     */
    void AudioPlayer::stopStream(unsigned int* audioStream)
    {
        if (std::find(streams.begin(), streams.end(), audioStream) != streams.end())
            alSourceStop(*audioStream);
        else
            logger("Stream not added", LOG_ERROR);
    }

    /**
     * set volume of every streams in player
     * @param volume Volume to be set 0%-100%
     */
    void AudioEngine::AudioPlayer::setGeneralVolume(unsigned int volume)
    {
        for(const unsigned int *stream : this->streams)
        {
            alSourcef(*stream, AL_GAIN, (float)volume / 100.0f);
        }
    }
}