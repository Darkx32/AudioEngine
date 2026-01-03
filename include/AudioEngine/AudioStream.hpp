#pragma once

namespace AudioEngine
{
    class AudioBuffer;
    class AudioEffects;
    class AudioStream
    {
    public:
        AudioStream() = default;
        /**
	     * Create a new AudioStream
	     * @param filepath Path to find audio file
	     */
        AudioStream(const char* filepath);
        ~AudioStream();

        /**
	     * Get the stream
	     * @return Stream
	     */
        unsigned int* getStream();

        /**
         * Get the internal AudioBuffer
         * @return AudioBuffer
         */
        AudioBuffer* getAudioBuffer() const;

        /**
	     * Set the volume of the stream on percentage format
	     * @param newVolume New volume
	     */
        void setVolume(int newVolume) const;
        /**
	     * Get the volume from stream on percentage format
	     * @return Value of volume
	     */
        int getVolume() const;
        /**
         * Set the pitch of the stream on percentage format
         * @param pitch New pitch
         */
        void setPitch(int pitch) const;
        /**
         * Get the pitch from stream on percentage format
         * @return Value of pitch
         */
        int getPitch() const;

        /**
         * Activate and disable loop on audio
         * @param toLoop Is to be looping
         */
        void enableLoop(bool toLoop) const;
        /**
         * Detect if is loop
         * @return Is loop
         */
        bool isLoop() const;

        /**
	     * Set the position of the stream
	     * @param x X position
	     * @param y Y position
	     * @param z Z position
	     */
        void setPosition(float x, float y, float z) const;
        /**
	     * Get the position from stream
	     * @return Return array with the coords [x, y, z]
	     */
        float* getPosition() const;
        /**
         * Set the direction from stream
         * @param x X direction
         * @param y Y direction
         * @param z Z direction
         */
        void setDirection(float x, float y, float z) const;
        /**
         * Get the direction from stream
	     * @return Return array with the coords [x, y, z]
         */
        float* getDirection() const;

        /**
         * Set the minimum distance to stop the volume from decreasing
         * @param refDistance 
         */
        void setReferenceDistance(float refDistance) const;
        /**
         * Get actual minimum distance to stop the volume from decreasing
         * @return New reference Distance
         */
        float getReferenceDistance() const;
        /**
         * Set max distance to hear the audio
         * @param maxDistance New max distance
         */
        void setMaxDistance(float maxDistance) const;
        /**
         * Get actual max distance to hear the audio
         * @return Max distance
         */
        float getMaxDistance() const;
        /**
         * Set the mitigation of the audio on percentage format
         * @param mitigation New mitigation
         */
        void setMitigation(int mitigation) const;
        /**
         * Get the mitigation of the audio on percentage format
         * @return Mitigation value
         */
        int getMitigation() const;

        /**
         * Get the internal effects
         * @return Internal AudioEffects
         */
        AudioEffects* getEffects() const;

    private:
        AudioBuffer* mAudioBuffer = nullptr;
        AudioEffects* mAudioEffects = nullptr;
        unsigned int mEffectSlot;

        unsigned int mStream;
    };
}