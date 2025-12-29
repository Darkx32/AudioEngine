#pragma once
#include <vector>

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
        void pauseStream(const unsigned int* audioStream);
        void stopStream(const unsigned int* audioStream);
        void setGeneralVolume(unsigned int volume) const;

    private:
        bool isPlayingAudio;

        std::vector<unsigned int*> streams;
    };
}