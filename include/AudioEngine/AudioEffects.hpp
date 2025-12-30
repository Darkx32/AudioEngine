#pragma once

namespace AudioEngine
{
	struct AudioReverb
	{
        float density;
        float diffusion;

        float gain;
        float gainHF;
        float gainLF;

        float decayTime;
        float decayHFRatio;
        float decayLFRatio;

        float reflectionsGain;
        float reflectionsDelay;
        float reflectionsPan[3];

        float lateReverbGain;
        float lateReverbDelay;
        float lateReverbPan[3];

        float echoTime;
        float echoDepth;

        float modulationTime;
        float modulationDepth;

        float airAbsorptionGainHF;
        float HFReference;
        float LFReference;

        float roomRolloffFactor = 0.0f;
        int   decayHFLimit = 1;

        static AudioReverb Default();
        static AudioReverb UnderWater();
        static AudioReverb SmallRoom();
        static AudioReverb LargeHall();
        static AudioReverb Cave();
        static AudioReverb Bathroom();
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
