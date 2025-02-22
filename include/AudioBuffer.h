#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace AudioEngine
{
	class AudioBuffer
	{
	public:
		AudioBuffer() = default;
		AudioBuffer(std::string);

		short getNumChannels();
		int getSampleRate();
		short getBitsPerSample();
		std::vector<uint8_t> getBufferData();

	private:
		int numChannels;
		int sampleRate;
		short bitsPerSample;
		int audioStreamIndex;

		std::vector<uint8_t> data;

		void getDetailsFromAudio(void*, void*, void*);
		void generateBufferData(void*, void*);
	};
}