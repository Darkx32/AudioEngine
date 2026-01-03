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
        /**
	     * Create a new AudioPlayer
	     */
        AudioPlayer();

        /**
         * Cleanup AudioPlayer
         */
        ~AudioPlayer();

        /**
	     * Update swaps of the player
	     */
        void updateSwaps();

        /**
	     * Check if audio is running
	     * @return True if audio is running
	     */
        bool isRunningAudio() const;

        /**
	     * Play a stream and save it to internal controller
	     * @param audioStream Stream to be played
	     */
        void playStream(unsigned int* audioStream);

        /**
	     * Pause a stream
	     * @param audioStream Stream to be paused
	     */
        void pauseStream(const unsigned int* audioStream);

        /**
	     * Stop a stream
	     * @param audioStream Stream to be stopped
	     */
        void stopStream(const unsigned int* audioStream);

        /**
	     * Set volume of every streams in player
	     * @param volume Volume to be set 0%-100%
	     */
        void setGeneralVolume(unsigned int volume) const;

        /**
         * Set distance model to address the sound distancing system
         * @param model 
         */
        static void setDistanceModel(DistanceModels model);

    private:
        bool isPlayingAudio;

        std::vector<unsigned int*> streams;
    };
}