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

        /**
         * Default preset
         * @return AudioReverb preset
         */
        static AudioReverb Default();

        /**
         * UnderWater preset
         * @return AudioReverb preset
         */
        static AudioReverb UnderWater();

        /**
         * SmallRoom preset
         * @return AudioReverb preset
         */
        static AudioReverb SmallRoom();

        /**
         * LargeHall preset
         * @return AudioReverb preset
         */
        static AudioReverb LargeHall();

        /**
         * Cave preset
         * @return AudioReverb preset
         */
        static AudioReverb Cave();

        /**
         * Bathroom preset
         * @return AudioReverb preset
         */
        static AudioReverb Bathroom();
	};

    class AudioStream;
	class AudioEffects
	{
	public:
		/**
		 * Create and define AudioEffects and your variables
		 */
		AudioEffects();

		/**
		 * Cleanup AudioEffects
		 */
		~AudioEffects();

		/**
		 * Update the actual preset
		 * @param reverb New preset
		 */
		void updateReverbEffect(const AudioReverb& reverb);

		/**
		 * Get actual preset
		 * @return Actual preset
		 */
		AudioReverb getActualReverbEffect() const;
	private:
        friend class AudioStream;

        AudioReverb mAudioReverb;
        unsigned int mEffectBuffer;
        unsigned int hasEAXSupport;

		/**
		 * Update all effects in OpenAL
		 */
		void updateEffectData() const;

		/**
		 * Get the effect buffer
		 * @return Effect buffer
		 */
		unsigned int& getEffectBuffer();
	};
}
