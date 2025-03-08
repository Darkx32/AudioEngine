#include <AudioEngine/AudioStream.hpp>
#include <AudioEngine/tools.hpp>
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
        if (audioBuffer.getBufferData().empty())
        {
            logger("AudioBuffer is empty", LOG_ERROR);
            return;
        }

        ALenum format, error;
        error = AL_NO_ERROR;
        ALuint buffer;
        unsigned int err = static_cast<unsigned int>(error);
        
        genBufferData(&buffer, audioBuffer, &format);
        this->hasOpenALError(&err);
        
        alGenSources(1, &this->stream);
        this->hasOpenALError(&err);

        alSourcei(this->stream, AL_BUFFER, (ALint)buffer);
        this->hasOpenALError(&err);
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
     * Get the volume from stream
     * @return Value of volume
     */
    int AudioStream::getVolume()
    {
        float actualVolume = 0;
        alGetSourcef(this->stream, AL_GAIN, &actualVolume);
        return static_cast<int>(actualVolume * 100.f);
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
     * Get the position from stream
     * @return Return array with the coords [x, y, z]
     */
    float* AudioStream::getPosition()
    {
        float x, y, z;
        alGetSource3f(this->stream, AL_POSITION, &x, &y, &z);
        static float position[] = {x, y, z};
        return position;
    }

    /**
     * Generate the buffer data
     * @param buffer OpenAL Buffer (is NULL)
     * @param audioBuffer audioBuffer
     * @param format audio format
     */
    void AudioStream::genBufferData(unsigned int* buffer, AudioBuffer audioBuffer, int* format)
    {
        ALuint error;
        alGenBuffers(1, buffer);
        this->hasOpenALError(&error);

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
        this->hasOpenALError(&error);
    }

    void AudioStream::hasOpenALError(unsigned int *error)
    {
        if ((*error = alGetError()) != AL_NO_ERROR)
        {
            const char* err = getErrorByOpenAL(*error);
            logger(err, LOG_ERROR);
            return;
        }
    }
}