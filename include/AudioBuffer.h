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

		int getFormat();
		short getNumChannels();
		int getSampleRate();
		short getBitsPerSample();
		int getChunkSize();
		std::vector<std::uint8_t> getData_8b();
		std::vector<std::uint16_t> getData_16b();

	private:
		//RIFF
		int chunkID;
		int chunkSize;
		int format;

		// FMT
		int subChunk1ID;
		int subChunk1Size;
		short audioFormat;
		short numChannels;
		int sampleRate;
		int byteRate;
		short blockAlign;
		short bitsPerSample;

		// DATA
		int subChunk2ID;
		int subChunk2Size;

		std::vector<std::uint8_t> data_8b;
		std::vector<std::uint16_t> data_16b;
	};
}