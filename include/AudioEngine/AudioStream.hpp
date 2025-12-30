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
        void setPosition(float x, float y, float z) const;
        float* getPosition() const;

        AudioEffects* getEffects() const;

    private:
        AudioBuffer* mAudioBuffer = nullptr;
        AudioEffects* mAudioEffects = nullptr;
        unsigned int mEffectSlot;

        unsigned int mStream;
    };
}