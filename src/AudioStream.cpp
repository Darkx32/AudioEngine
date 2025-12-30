#include <AudioEngine/AudioStream.hpp>
#include <AudioEngine/tools.hpp>
#include <AudioEngine/AudioBuffer.hpp>
#include <AudioEngine/AudioEffects.hpp>

#define AL_ALEXT_PROTOTYPES
#include <AL/al.h>
#include <AL/efx.h>
#include <iostream>


namespace AudioEngine
{
    /**
     * Create a new AudioStream
     * @param filepath Path to find audio file
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
        
        unsigned int error = AL_NO_ERROR;
        
        alGenSources(1, &mStream);
        hasOpenALError(&error);

        alSourcei(mStream, AL_BUFFER, (ALint)mAudioBuffer->getBuffer());
        hasOpenALError(&error);

        if (alcIsExtensionPresent(alcGetContextsDevice(alcGetCurrentContext()), "ALC_EXT_EFX")) {
            mAudioEffects = new AudioEffects();
            alGenAuxiliaryEffectSlots(1, &mEffectSlot);
            alAuxiliaryEffectSloti(mEffectSlot, AL_EFFECTSLOT_EFFECT, static_cast<ALint>(mAudioEffects->getEffectBuffer()));
            alSource3i(mStream, AL_AUXILIARY_SEND_FILTER, static_cast<ALint>(mEffectSlot), 0, AL_FILTER_NULL);
        }
    }

    AudioStream::~AudioStream()
    {
        if (alIsSource(mStream))
			alDeleteSources(1, &mStream);
        if (alIsAuxiliaryEffectSlot(mEffectSlot))
            alDeleteAuxiliaryEffectSlots(1, &mEffectSlot);
        RELEASE(mAudioBuffer);
        RELEASE(mAudioEffects);
    }

    /**
     * Get the stream
     * @return Stream
     */
    unsigned int* AudioStream::getStream()
    {
        return &mStream;
    }

    AudioBuffer* AudioStream::getAudioBuffer() const
    {
        return mAudioBuffer;
    }

    /**
     * Set the volume of the stream
     * @param newVolume New volume
     */
    void AudioStream::setVolume(const int newVolume) const
    {
        alSourcef(mStream, AL_GAIN, static_cast<ALfloat>(newVolume) / 100.f);
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
}