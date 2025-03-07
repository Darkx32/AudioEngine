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
        void setPosition(float x, float y, float z);

    private:
        void genBufferData(unsigned int*, AudioBuffer, int*);

        unsigned int stream;
    };
}