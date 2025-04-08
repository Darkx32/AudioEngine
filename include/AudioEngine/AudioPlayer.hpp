#pragma once
#include "AudioStream.hpp"

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
        void pauseStream(unsigned int*);
        void stopStream(unsigned int*);
        void setGeneralVolume(unsigned int);

    private:
        bool isPlayingAudio;

        std::vector<unsigned int*> streams;
    };
}