#include <AudioBuffer.h>
#include <stdio.h>
#include <iostream>
#include "tools.h"
#include <AL/al.h>

namespace AudioEngine
{
    AudioBuffer::AudioBuffer(std::string file)
    {
        FILE* fb;

        #ifdef _WIN32
        fopen_s(&fb, file.c_str(), "rb");
        #elif linux
        fb = fopen64(file.c_str(), "rb");
        #endif


        // Reading RIFF from WAVE file
        fread(&this->chunkID, sizeof(int), 1, fb);
        fread(&this->chunkSize, sizeof(int), 1, fb);
        fread(&this->format, sizeof(int), 1, fb);

        // Reading FMT from WAVE file
        fread(&this->subChunk1ID, sizeof(int), 1, fb);
        fread(&this->subChunk1Size, sizeof(int), 1, fb);
        fread(&this->audioFormat, sizeof(short), 1, fb);
        fread(&this->numChannels, sizeof(short), 1, fb);
        fread(&this->sampleRate, sizeof(int), 1, fb);
        fread(&this->byteRate, sizeof(int), 1, fb);
        fread(&this->blockAlign, sizeof(short), 1, fb);
        fread(&this->bitsPerSample, sizeof(short), 1, fb);

        // Reading DATA-INFO from WAVE file
        fread(&this->subChunk2ID, sizeof(int), 1, fb);
        fread(&this->subChunk2Size, sizeof(int), 1, fb);

        // Reading DATA from WAVE file
        if (this->bitsPerSample == 8)
        {
            uint8_t buffer_8b;

            while(fread(&buffer_8b, sizeof(uint8_t), 1, fb))
                data_8b.push_back(buffer_8b);
        } else if (this->bitsPerSample == 16)
        {
            uint16_t buffer_16b;

            while(fread(&buffer_16b, sizeof(uint16_t), 1, fb))
                data_16b.push_back(buffer_16b);
        }

        fclose(fb);
    }

    int AudioBuffer::getFormat()
    {
        return this->format;
    }

    short AudioBuffer::getNumChannels()
    {
        return this->numChannels;
    }

    int AudioBuffer::getSampleRate()
    {
        return this->sampleRate;
    }

    int AudioBuffer::getChunkSize()
    {
        return this->subChunk2Size;
    }

    short AudioBuffer::getBitsPerSample()
    {
        return this->bitsPerSample;
    }

    std::vector<std::uint8_t> AudioBuffer::getData_8b()
    {
        return this->data_8b;
    }

    std::vector<std::uint16_t> AudioBuffer::getData_16b()
    {
        return this->data_16b;
    }
}