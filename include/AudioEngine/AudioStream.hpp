#pragma once
#include "AudioBuffer.hpp"

namespace AudioEngine
{
    class AudioStream
    {
    public:
        AudioStream() = default;
        AudioStream(AudioBuffer);
        ~AudioStream();

        unsigned int* getStream();
        void setVolume(int newVolume);
        int getVolume();
        void setPosition(float x, float y, float z);
        float* getPosition();

    private:
        void genBufferData(unsigned int*, AudioBuffer, int*);
        void hasOpenALError(unsigned int*);

        unsigned int stream;
    };
}