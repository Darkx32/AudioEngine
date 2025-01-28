#pragma once
#include "AudioBuffer.h"

namespace AudioEngine
{
    class AudioStream
    {
    public:
        AudioStream() = default;
        AudioStream(AudioBuffer);
        ~AudioStream();

        unsigned int* getStream();

    private:
        void genBufferData(unsigned int*, AudioBuffer, int*);

        unsigned int stream;
    };
}