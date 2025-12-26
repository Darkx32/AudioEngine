#pragma once

namespace AudioEngine
{
    class AudioBuffer;
    class AudioStream
    {
    public:
        AudioStream() = default;
        AudioStream(const char* filepath);
        ~AudioStream();

        unsigned int* getStream();
        AudioBuffer* getAudioBuffer();
        void setVolume(int newVolume) const;
        int getVolume() const;
        void setPosition(float x, float y, float z) const;
        float* getPosition() const;

    private:
        AudioBuffer* mAudioBuffer;

        void genBufferData(unsigned int* buffer, int* format);
        void hasOpenALError(unsigned int* error);

        unsigned int mStream;
    };
}