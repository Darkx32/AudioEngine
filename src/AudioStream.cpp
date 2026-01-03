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
    AudioStream::AudioStream(const char* filepath)
    {
        mStream = -1;
        mAudioBuffer = new AudioBuffer(filepath);

        if (mAudioBuffer->getBufferData().empty())
        {
            logger(LOG_ERROR, "AudioBuffer is empty");
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

    unsigned int* AudioStream::getStream()
    {
        return &mStream;
    }

    AudioBuffer* AudioStream::getAudioBuffer() const
    {
        return mAudioBuffer;
    }

    AudioEffects* AudioStream::getEffects() const
    {
        return mAudioEffects;
    }
}
