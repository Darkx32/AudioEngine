#include "AudioStream.h"
#include <AL/al.h>
#include <AL/alext.h>
#include <iostream>

namespace AudioEngine
{
    AudioStream::AudioStream(AudioBuffer audioBuffer)
    {
        ALenum format, error;
        ALuint buffer;
        
        genBufferData(&buffer, audioBuffer, &format);
        if ((error = alGetError()) != AL_NO_ERROR)
            std::cout << error << std::endl;
        
        alGenSources(1, &this->stream);
        alSourcei(this->stream, AL_BUFFER, (ALint)buffer);
        if ((error = alGetError()) != AL_NO_ERROR)
            std::cout << error << std::endl;
    }

    AudioStream::~AudioStream()
    {
        alDeleteSources(1, &this->stream);
    }

    unsigned int* AudioStream::getStream()
    {
        return &this->stream;
    }

    void AudioStream::genBufferData(unsigned int* buffer, AudioBuffer audioBuffer, int* format)
    {
        short numChannels = audioBuffer.getNumChannels();
        alGenBuffers(1, buffer);

        if (audioBuffer.getBitsPerSample() == 8){
            if (numChannels == 1)
                *format = AL_FORMAT_MONO8;
            else if (numChannels == 2)
                *format = AL_FORMAT_STEREO8;
            else if (numChannels == 3)
                *format = AL_FORMAT_BFORMAT2D_8;
            else if (numChannels == 4)
                *format = AL_FORMAT_BFORMAT3D_8;

            alBufferData(*buffer, (ALenum)*format, audioBuffer.getData_8b().data(), audioBuffer.getChunkSize(), audioBuffer.getSampleRate());
        } else if (audioBuffer.getBitsPerSample() == 16)
        {
            if (numChannels == 1)
                *format = AL_FORMAT_MONO16;
            else if (numChannels == 2)
                *format = AL_FORMAT_STEREO16;
            else if (numChannels == 3)
                *format = AL_FORMAT_BFORMAT2D_16;
            else if (numChannels == 4)
                *format = AL_FORMAT_BFORMAT3D_16;

            alBufferData(*buffer, (ALenum)*format, audioBuffer.getData_16b().data(), audioBuffer.getChunkSize(), audioBuffer.getSampleRate());
        }
    }
}