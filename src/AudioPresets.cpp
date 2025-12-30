#include <AudioEngine/AudioEffects.hpp>

namespace AudioEngine
{
	AudioReverb AudioReverb::Default()
	{
        return {
        1.0f, 1.0f,

        0.32f, 0.89f, 1.0f,

        1.49f, 0.83f, 1.0f,

        0.05f, 0.007f, { 0.0f, 0.0f, 0.0f },

        1.26f, 0.011f, { 0.0f, 0.0f, 0.0f },

        0.25f, 0.0f,

        0.25f, 0.0f,

        0.994f, 5000.0f, 250.0f,

        0.0f, 1
        };
	}

	AudioReverb AudioReverb::UnderWater()
	{
        return {
        0.364f, 0.42f,

        0.25f, 0.10f, 1.0f,

        1.49f, 0.10f, 1.0f,

        0.007f, 0.011f, { 0.0f, 0.0f, 0.0f },

        1.26f, 0.011f, { 0.0f, 0.0f, 0.0f },

        0.25f, 0.0f,

        0.25f, 0.0f,

        0.994f, 5000.0f, 250.0f,

        0.0f, 1
        };
	}

    AudioReverb AudioReverb::SmallRoom()
    {
        return {
            1.0f, 0.70f,

            0.30f, 0.80f, 1.0f,

            0.80f, 0.90f, 1.0f,

            0.20f, 0.004f, { 0.0f, 0.0f, 0.0f },

            1.00f, 0.010f, { 0.0f, 0.0f, 0.0f },

            0.25f, 0.0f,

            0.25f, 0.0f,

            0.994f, 5000.0f, 250.0f,

            0.0f, 1
        };
    }

    AudioReverb AudioReverb::LargeHall()
    {
        return {
            1.0f, 1.0f,

            0.28f, 0.70f, 1.0f,

            3.50f, 0.70f, 1.0f,

            0.10f, 0.020f, { 0.0f, 0.0f, 0.0f },

            1.50f, 0.030f, { 0.0f, 0.0f, 0.0f },

            0.25f, 0.0f,

            0.25f, 0.0f,

            0.994f, 5000.0f, 250.0f,

            0.0f, 1
        };
    }

    AudioReverb AudioReverb::Cave()
    {
        return {
            1.0f, 0.90f,

            0.35f, 0.50f, 1.0f,

            2.90f, 0.60f, 1.0f,

            0.15f, 0.015f, { 0.0f, 0.0f, 0.0f },

            1.80f, 0.022f, { 0.0f, 0.0f, 0.0f },

            0.25f, 0.0f,

            0.25f, 0.0f,

            0.994f, 5000.0f, 250.0f,

            0.0f, 1
        };
    }

    AudioReverb AudioReverb::Bathroom()
    {
        return {
            1.0f, 0.30f,

            0.45f, 0.95f, 1.0f,

            1.10f, 0.90f, 1.0f,

            0.40f, 0.005f, { 0.0f, 0.0f, 0.0f },

            1.20f, 0.010f, { 0.0f, 0.0f, 0.0f },

            0.25f, 0.0f,

            0.25f, 0.0f,

            0.994f, 5000.0f, 250.0f,

            0.0f, 1
        };
    }
}
