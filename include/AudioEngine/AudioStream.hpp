#pragma once

namespace AudioEngine
{
    class AudioBuffer;
    class AudioEffects;
    class AudioStream
    {
    public:
        AudioStream() = default;
        AudioStream(const char* filepath);
        ~AudioStream();

        unsigned int* getStream();
        AudioBuffer* getAudioBuffer() const;

        void setVolume(int newVolume) const;
        int getVolume() const;
        void setPitch(int pitch) const;
        int getPitch() const;

        void enableLoop(bool toLoop) const;
        bool isLoop() const;

        void setPosition(float x, float y, float z) const;
        float* getPosition() const;
        void setDirection(float x, float y, float z) const;
        float* getDirection() const;

        void setReferenceDistance(float refDistance) const;
        float getReferenceDistance() const;
        void setMaxDistance(float maxDistance) const;
        float getMaxDistance() const;
        void setMitigation(int mitigation) const;
        int getMitigation() const;

        AudioEffects* getEffects() const;

    private:
        AudioBuffer* mAudioBuffer = nullptr;
        AudioEffects* mAudioEffects = nullptr;
        unsigned int mEffectSlot;

        unsigned int mStream;
    };
}