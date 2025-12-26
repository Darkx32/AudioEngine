#include <AudioEngine/AudioStream.hpp>
#include <AudioEngine/tools.hpp>
#include <AL/al.h>
#include <AL/alext.h>
#include <iostream>
#include "AudioEngine/AudioBuffer.hpp"

namespace AudioEngine
{
    /**
     * Create a new AudioStream
     * @param audioBuffer Buffer for processing data
     */
    AudioStream::AudioStream(const char* filepath)
    {
        mStream = -1;
        mAudioBuffer = new AudioBuffer(filepath);

        if (mAudioBuffer->getBufferData().empty())
        {
            logger("AudioBuffer is empty", LOG_ERROR);
            return;
        }

        ALenum format, error;
        error = AL_NO_ERROR;
        ALuint buffer;
        unsigned int err = static_cast<unsigned int>(error);
        
        genBufferData(&buffer, &format);
        hasOpenALError(&err);
        
        alGenSources(1, &mStream);
        hasOpenALError(&err);

        alSourcei(mStream, AL_BUFFER, (ALint)buffer);
        hasOpenALError(&err);
    }

    AudioStream::~AudioStream()
    {
        alDeleteSources(1, &mStream);
        RELEASE(mAudioBuffer);
    }

    /**
     * Get the stream
     * @return Stream
     */
    unsigned int* AudioStream::getStream()
    {
        return &mStream;
    }

    AudioBuffer* AudioStream::getAudioBuffer() {
        return mAudioBuffer;
    }

    /**
     * Set the volume of the stream
     * @param newVolume New volume
     */
    void AudioStream::setVolume(int newVolume) const
    {
        alSourcef(mStream, AL_GAIN, newVolume / 100.f);
    }

    /**
     * Get the volume from stream
     * @return Value of volume
     */
    int AudioStream::getVolume() const
    {
        float actualVolume = 0;
        alGetSourcef(mStream, AL_GAIN, &actualVolume);
        return static_cast<int>(actualVolume * 100.f);
    } 

    /**
     * Set the position of the stream
     * @param x X position
     */
    void AudioStream::setPosition(float x, float y, float z) const
    {
        alSource3f(mStream, AL_POSITION, x, y, z);
    }

    /**
     * Get the position from stream
     * @return Return array with the coords [x, y, z]
     */
    float* AudioStream::getPosition() const
    {
        float x, y, z;
        alGetSource3f(mStream, AL_POSITION, &x, &y, &z);
        static float position[] = {x, y, z};
        return position;
    }

    /**
     * Generate the buffer data
     * @param buffer OpenAL Buffer (is NULL)
     * @param audioBuffer audioBuffer
     * @param format audio format
     */
    void AudioStream::genBufferData(unsigned int* buffer, int* format)
    {
        ALuint error;
        alGenBuffers(1, buffer);
        hasOpenALError(&error);

        if (mAudioBuffer->getBitsPerSample() == 8)
        {
            if (mAudioBuffer->getNumChannels() == 1)
                *format = AL_FORMAT_MONO8;
            else if (mAudioBuffer->getNumChannels() == 2)
                *format = AL_FORMAT_STEREO8;
        } else
        {
            if (mAudioBuffer->getNumChannels() == 1)
                *format = AL_FORMAT_MONO16;
            else if (mAudioBuffer->getNumChannels() == 2)
                *format = AL_FORMAT_STEREO16;
        }
        

        alBufferData(*buffer, (ALenum)*format, mAudioBuffer->getBufferData().data(), static_cast<ALsizei>(mAudioBuffer->getBufferData().size()), mAudioBuffer->getSampleRate());
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