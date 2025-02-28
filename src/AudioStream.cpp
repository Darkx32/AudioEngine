#include "AudioStream.h"
#include <AL/al.h>
#include <AL/alext.h>
#include <iostream>

namespace AudioEngine
{
    /**
     * Create a new AudioStream
     * @param audioBuffer Buffer for processing data
     */
    AudioStream::AudioStream(AudioBuffer audioBuffer)
    {
        ALenum format, error;
        ALuint buffer;
        
        genBufferData(&buffer, audioBuffer, &format);
        if ((error = alGetError()) != AL_NO_ERROR)
            std::cout << error << std::endl;
        
        alGenSources(1, &this->stream);
        if ((error = alGetError()) != AL_NO_ERROR)
            std::cout << error << std::endl;

        alSourcei(this->stream, AL_BUFFER, (ALint)buffer);
        if ((error = alGetError()) != AL_NO_ERROR)
            std::cout << error << std::endl;
    }

    AudioStream::~AudioStream()
    {
        alDeleteSources(1, &this->stream);
    }

    /**
     * Get the stream
     * @return Stream
     */
    unsigned int* AudioStream::getStream()
    {
        return &this->stream;
    }

    /**
     * Set the volume of the stream
     * @param newVolume New volume
     */
    void AudioStream::setVolume(int newVolume)
    {
        alSourcef(this->stream, AL_GAIN, newVolume / 100.f);
    }

    /**
     * Set the position of the stream
     * @param x X position
     */
    void AudioStream::setPosition(float x, float y, float z)
    {
        alSource3f(this->stream, AL_POSITION, x, y, z);
    }

    /**
     * Generate the buffer data
     * @param buffer OpenAL Buffer (is NULL)
     * @param audioBuffer audioBuffer
     * @param format audio format
     */
    void AudioStream::genBufferData(unsigned int* buffer, AudioBuffer audioBuffer, int* format)
    {
        alGenBuffers(1, buffer);

        if (audioBuffer.getBitsPerSample() == 8)
        {
            if (audioBuffer.getNumChannels() == 1)
                *format = AL_FORMAT_MONO8;
            else if (audioBuffer.getNumChannels() == 2)
                *format = AL_FORMAT_STEREO8;
        } else
        {
            if (audioBuffer.getNumChannels() == 1)
                *format = AL_FORMAT_MONO16;
            else if (audioBuffer.getNumChannels() == 2)
                *format = AL_FORMAT_STEREO16;
        }
        

        alBufferData(*buffer, (ALenum)*format, audioBuffer.getBufferData().data(), audioBuffer.getBufferData().size(), audioBuffer.getSampleRate());
    }
}