#pragma once
#include <vector>

namespace AudioEngine
{
	enum DistanceModels
	{
        AE_INVERSE_DISTANCE = 0xD001,
        AE_INVERSE_DISTANCE_CLAMPED = 0xD002,
        AE_LINEAR_DISTANCE = 0xD003,
        AE_LINEAR_DISTANCE_CLAMPED = 0xD004,
        AE_EXPONENT_DISTANCE = 0xD005,
        AE_EXPONENT_DISTANCE_CLAMPED = 0xD006
	};

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
        static void setDistanceModel(DistanceModels model);

    private:
        bool isPlayingAudio;

        std::vector<unsigned int*> streams;
    };
}