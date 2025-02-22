#include "AudioPlayer.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <tools.h>
#include <algorithm>
extern "C"
{
    #include <libavfilter/avfilter.h>
}


namespace AudioEngine
{
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

    void AudioPlayer::addStream(unsigned int* audioStream)
    {
        if (std::find(streams.begin(), streams.end(), audioStream) != streams.end())
            logger("Stream already added", LOG_WARN);
        else
            this->streams.push_back(audioStream);
    }

    void AudioPlayer::updateSwaps()
    {
        ALenum error, state;
        if ((error = alGetError()) != AL_NO_ERROR)
            logger(getErrorByOpenAL(error), LOG_ERROR);

        isPlayingAudio = false;

        for(unsigned int* stream : this->streams)
        {
            alGetSourcei(*stream, AL_SOURCE_STATE, &state);
            if (state == AL_PLAYING || state == AL_INITIAL) 
            {
                this->isPlayingAudio = true;
                break;
            }
        }
    }

    bool AudioPlayer::isRunningAudio()
    {
        return this->isPlayingAudio;
    }
    
    void AudioPlayer::playStream(unsigned int * source)
    {
        alSourcePlay(*source);
    }
}