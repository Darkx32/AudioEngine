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
		/**
		 * Create a Audio Buffer
		 * @param file path to audio file
		 */
		AudioBuffer(const std::string& file);
		/**
		 * Cleanup AudioBuffer
		 */
		~AudioBuffer();

		/**
		 * Get number of channels
		 * @return Number of channels
		 */
		int getNumChannels() const;

		/**
		 * Get sample rate from audio file
		 * @return Sample rate
		 */
		int getSampleRate() const;

		/**
		 * Get bits per sample from audio file
		 * @return Bits per sample
		 */
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

		/**
		 * Get audio data in vector that contains bytes
		 * @return Vector with bytes
		 */
		std::vector<uint8_t> getBufferData();
		unsigned int& getBuffer();

		/**
		 * Get audio file details and save it in variables on class
		 * @param fc AVFormatContext
		 * @param cc AVCodecContext
		 * @param cp AVCodecParameters
		 */
		void getDetailsFromAudio(void* fc, void* cc, void* cp);

		/**
		 * Generate audio buffer to play
		 * @param fc AVFormatContext
		 * @param cc AVCodecContext
		 */
		void generateBufferData(void* fc, void* cc);

		/**
		 * Generate the buffer data
		 */
		void genBufferData();
	};
}