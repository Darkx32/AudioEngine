#include "AudioEngine/AudioEffects.hpp"
#include "AudioEngine/tools.hpp"

#define AL_ALEXT_PROTOTYPES
#include <AL/al.h>
#include <AL/efx.h>

namespace AudioEngine
{
	AudioEffects::AudioEffects()
	{
		alGenEffects(1, &mEffectBuffer);
		alEffecti(mEffectBuffer, AL_EFFECT_TYPE, AL_EFFECT_EAXREVERB);
		unsigned int err;
		hasOpenALError(&err);
		hasEAXSupport = err == AL_NO_ERROR;

		updateEffectData();
	}

	AudioEffects::~AudioEffects()
	{
		if (alIsEffect(mEffectBuffer))
			alDeleteEffects(1, &mEffectBuffer);
	}

	void AudioEffects::updateReverbEffect(const AudioReverb& reverb)
	{
		mAudioReverb = reverb;
		updateEffectData();
	}

	AudioReverb AudioEffects::getActualReverbEffect() const
	{
		return mAudioReverb;
	}

	void AudioEffects::updateEffectData() const
	{
		if (hasEAXSupport)
		{
			alEffectf(mEffectBuffer, AL_EAXREVERB_DENSITY, mAudioReverb.density);
			alEffectf(mEffectBuffer, AL_EAXREVERB_DIFFUSION, mAudioReverb.diffusion);
			alEffectf(mEffectBuffer, AL_EAXREVERB_GAIN, mAudioReverb.gain);
			alEffectf(mEffectBuffer, AL_EAXREVERB_GAINHF, mAudioReverb.gainHF);
			alEffectf(mEffectBuffer, AL_EAXREVERB_GAINLF, mAudioReverb.gainLF);
			alEffectf(mEffectBuffer, AL_EAXREVERB_DECAY_TIME, mAudioReverb.decayTime);
			alEffectf(mEffectBuffer, AL_EAXREVERB_DECAY_HFRATIO, mAudioReverb.decayHFRatio);
			alEffectf(mEffectBuffer, AL_EAXREVERB_DECAY_LFRATIO, mAudioReverb.decayLFRatio);
			alEffectf(mEffectBuffer, AL_EAXREVERB_REFLECTIONS_GAIN, mAudioReverb.reflectionsGain);
			alEffectf(mEffectBuffer, AL_EAXREVERB_REFLECTIONS_DELAY, mAudioReverb.reflectionsDelay);
			alEffectfv(mEffectBuffer, AL_EAXREVERB_REFLECTIONS_PAN, mAudioReverb.reflectionsPan);
			alEffectf(mEffectBuffer, AL_EAXREVERB_LATE_REVERB_GAIN, mAudioReverb.lateReverbGain);
			alEffectf(mEffectBuffer, AL_EAXREVERB_LATE_REVERB_DELAY, mAudioReverb.lateReverbDelay);
			alEffectfv(mEffectBuffer, AL_EAXREVERB_LATE_REVERB_PAN, mAudioReverb.lateReverbPan);
			alEffectf(mEffectBuffer, AL_EAXREVERB_ECHO_TIME, mAudioReverb.echoTime);
			alEffectf(mEffectBuffer, AL_EAXREVERB_ECHO_DEPTH, mAudioReverb.echoDepth);
			alEffectf(mEffectBuffer, AL_EAXREVERB_MODULATION_TIME, mAudioReverb.modulationTime);
			alEffectf(mEffectBuffer, AL_EAXREVERB_MODULATION_DEPTH, mAudioReverb.modulationDepth);
			alEffectf(mEffectBuffer, AL_EAXREVERB_AIR_ABSORPTION_GAINHF, mAudioReverb.airAbsorptionGainHF);
			alEffectf(mEffectBuffer, AL_EAXREVERB_HFREFERENCE, mAudioReverb.HFReference);
			alEffectf(mEffectBuffer, AL_EAXREVERB_LFREFERENCE, mAudioReverb.LFReference);
			alEffectf(mEffectBuffer, AL_EAXREVERB_ROOM_ROLLOFF_FACTOR, mAudioReverb.roomRolloffFactor);
			alEffecti(mEffectBuffer, AL_EAXREVERB_DECAY_HFLIMIT, mAudioReverb.decayHFLimit);
		} else
		{
			alEffecti(mEffectBuffer, AL_EFFECT_TYPE, AL_EFFECT_REVERB);

			alEffectf(mEffectBuffer, AL_REVERB_DENSITY, mAudioReverb.density);
			alEffectf(mEffectBuffer, AL_REVERB_DIFFUSION, mAudioReverb.diffusion);
			alEffectf(mEffectBuffer, AL_REVERB_GAIN, mAudioReverb.gain);
			alEffectf(mEffectBuffer, AL_REVERB_GAINHF, mAudioReverb.gainHF);
			alEffectf(mEffectBuffer, AL_REVERB_DECAY_TIME, mAudioReverb.decayTime);
			alEffectf(mEffectBuffer, AL_REVERB_DECAY_HFRATIO, mAudioReverb.decayHFRatio);
			alEffectf(mEffectBuffer, AL_REVERB_REFLECTIONS_GAIN, mAudioReverb.reflectionsGain);
			alEffectf(mEffectBuffer, AL_REVERB_REFLECTIONS_DELAY, mAudioReverb.reflectionsDelay);
			alEffectf(mEffectBuffer, AL_REVERB_LATE_REVERB_GAIN, mAudioReverb.lateReverbGain);
			alEffectf(mEffectBuffer, AL_REVERB_LATE_REVERB_DELAY, mAudioReverb.lateReverbDelay);
			alEffectf(mEffectBuffer, AL_REVERB_AIR_ABSORPTION_GAINHF, mAudioReverb.airAbsorptionGainHF);
			alEffectf(mEffectBuffer, AL_REVERB_ROOM_ROLLOFF_FACTOR, mAudioReverb.roomRolloffFactor);
			alEffecti(mEffectBuffer, AL_REVERB_DECAY_HFLIMIT, mAudioReverb.decayHFLimit);
		}
	}

	unsigned int& AudioEffects::getEffectBuffer()
	{
		return mEffectBuffer;
	}
}
