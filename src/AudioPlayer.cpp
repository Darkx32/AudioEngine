#include "AudioPlayer.h"
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>
#include <thread>
#include <chrono>
#include <iostream>

namespace AudioEngine
{
    AudioPlayer::AudioPlayer()
    {
        ALCdevice* device = alcOpenDevice(NULL);
        ALCcontext* context = alcCreateContext(device, NULL);
        alcMakeContextCurrent(context);

        isPlayingAudio = true;
    }

    AudioPlayer::~AudioPlayer()
    {
        this->streams.clear();
    }

    void AudioPlayer::addStream(unsigned int* audioStream)
    {
        this->streams.push_back(audioStream);
    }

    void AudioPlayer::updateSwaps()
    {
        std::this_thread::sleep_for(std::chrono::nanoseconds(10000000));
        ALenum error, state;
        if ((error = alGetError()) != AL_NO_ERROR)
            std::cout << error << std::endl;

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

    bool AudioPlayer::isRunningAudio()
    {
        return this->isPlayingAudio;
    }
    void AudioPlayer::playStream(unsigned int * source)
    {
        alSourcePlay(*source);
    }
}