#pragma once
#include <vector>
#include "AudioStream.hpp"

namespace AudioEngine
{
    class AudioPlayer
    {
    public:
        AudioPlayer();
        ~AudioPlayer();

        void updateSwaps();
        bool isRunningAudio() const;
        void playStream(unsigned int* audioStream);
        void pauseStream(unsigned int* audioStream);
        void stopStream(unsigned int* audioStream);
        void setGeneralVolume(unsigned int volume);

    private:
        bool isPlayingAudio;

        std::vector<unsigned int*> streams;
    };
}