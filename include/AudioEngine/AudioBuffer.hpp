#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace AudioEngine
{
	class AudioStream;
	class AudioBuffer
	{
	public:
		AudioBuffer(const std::string& file);
		~AudioBuffer();

		int getNumChannels() const;
		int getSampleRate() const;
		short getBitsPerSample() const;

	private:
		friend class AudioStream;
		int mNumChannels;
		int mSampleRate;
		short mBitsPerSample;
		int mAudioStreamIndex;
		unsigned int mFormat;
		unsigned int mBuffer;

		std::vector<uint8_t> mData;
		std::vector<uint8_t> getBufferData();
		unsigned int& getBuffer();
		
		void genBufferData();
		void getDetailsFromAudio(void* fc, void* cc, void* cp);
		void generateBufferData(void* fc, void* cc);
	};
}