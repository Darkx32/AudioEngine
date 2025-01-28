#pragma once
#include "AudioStream.h"

namespace AudioEngine
{
    class AudioPlayer
    {
    public:
        AudioPlayer();
        ~AudioPlayer();

        void addStream(unsigned int*);
        void updateSwaps();
        bool isRunningAudio();
        void playStream(unsigned int*);

    private:
        bool isPlayingAudio;

        std::vector<unsigned int*> streams;
    };
}