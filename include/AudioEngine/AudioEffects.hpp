#pragma once

namespace AudioEngine
{
	struct AudioReverb
	{
        float density = 1.0f;
        float diffusion = 1.0f;

        float gain = 0.32f;
        float gainHF = 0.89f;
        float gainLF = 1.0f;

        float decayTime = 1.49f;
        float decayHFRatio = 0.83f;
        float decayLFRatio = 1.0f;

        float reflectionsGain = 0.05f;
        float reflectionsDelay = 0.007f;
        float reflectionsPan[3] = { 0.0f, 0.0f, 0.0f };

        float lateReverbGain = 1.26f;
        float lateReverbDelay = 0.011f;
        float lateReverbPan[3] = { 0.0f, 0.0f, 0.0f };

        float echoTime = 0.25f;
        float echoDepth = 0.0f;

        float modulationTime = 0.25f;
        float modulationDepth = 0.0f;

        float airAbsorptionGainHF = 0.994f;
        float HFReference = 5000.0f;
        float LFReference = 250.0f;

        float roomRolloffFactor = 0.0f;
        int   decayHFLimit = 1;
	};

    class AudioStream;
	class AudioEffects
	{
	public:
		AudioEffects();
        ~AudioEffects();

        void updateReverbEffect(const AudioReverb& reverb);
        AudioReverb getActualReverbEffect() const;
	private:
        friend class AudioStream;

        AudioReverb mAudioReverb;
        unsigned int mEffectBuffer;
        unsigned int hasEAXSupport;

        void updateEffectData() const;
        unsigned int& getEffectBuffer();
	};
}
