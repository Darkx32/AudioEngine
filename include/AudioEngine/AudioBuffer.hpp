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

		short getNumChannels() const;
		int getSampleRate() const;
		short getBitsPerSample() const;
		std::vector<uint8_t> getBufferData();

	private:
		int numChannels;
		int sampleRate;
		short bitsPerSample;
		int audioStreamIndex;

		std::vector<uint8_t> data;

		void getDetailsFromAudio(void* fc, void* cc, void* cp);
		void generateBufferData(void* fc, void* cc);
	};
}