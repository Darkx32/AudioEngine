#include <AudioEngine/AudioStream.hpp>
#include <AL/al.h>

namespace AudioEngine
{
    void AudioStream::setVolume(const int newVolume) const
    {
        alSourcef(mStream, AL_GAIN, static_cast<ALfloat>(newVolume) / 100.f);
    }

    int AudioStream::getVolume() const
    {
        float actualVolume = 0;
        alGetSourcef(mStream, AL_GAIN, &actualVolume);
        return static_cast<int>(actualVolume * 100.f);
    }

    void AudioStream::setPitch(const int pitch) const
    {
        alSourcef(mStream, AL_PITCH, static_cast<ALfloat>(pitch) / 100.f);
    }

    int AudioStream::getPitch() const
    {
        float pitch = 0;
        alGetSourcef(mStream, AL_PITCH, &pitch);
        return static_cast<int>(pitch * 100);
    }

    void AudioStream::enableLoop(const bool toLoop) const
    {
        alSourcei(mStream, AL_LOOPING, toLoop);
    }

    bool AudioStream::isLoop() const
    {
        ALint isLoop = false;
        alGetSourcei(mStream, AL_LOOPING, &isLoop);
        return static_cast<bool>(isLoop);
    }

    void AudioStream::setPosition(const float x, const float y, const float z) const
    {
        alSource3f(mStream, AL_POSITION, x, y, z);
    }

    float* AudioStream::getPosition() const
    {
        float x, y, z;
        alGetSource3f(mStream, AL_POSITION, &x, &y, &z);
        static float position[] = { x, y, z };
        return position;
    }

    void AudioStream::setDirection(const float x, const float y, const float z) const
    {
        alSource3f(mStream, AL_DIRECTION, x, y, z);
    }

    float* AudioStream::getDirection() const
    {
        float x, y, z;
        alGetSource3f(mStream, AL_DIRECTION, &x, &y, &z);
        static float direction[] = {x, y, z};
        return direction;
    }

    void AudioStream::setReferenceDistance(const float refDistance) const
    {
        alSourcef(mStream, AL_REFERENCE_DISTANCE, refDistance);
    }

    float AudioStream::getReferenceDistance() const
    {
        float refDistance = 0;
        alGetSourcef(mStream, AL_REFERENCE_DISTANCE, &refDistance);
        return refDistance;
    }

    void AudioStream::setMaxDistance(const float maxDistance) const
    {
        alSourcef(mStream, AL_MAX_DISTANCE, maxDistance);
    }

    float AudioStream::getMaxDistance() const
    {
        float maxDistance = 0.0f;
        alGetSourcef(mStream, AL_MAX_DISTANCE, &maxDistance);
        return maxDistance;
    }

    void AudioStream::setMitigation(const int mitigation) const
    {
        alSourcef(mStream, AL_ROLLOFF_FACTOR, static_cast<ALfloat>(mitigation) / 100.f);
    }

    int AudioStream::getMitigation() const
    {
        float mitigation = 0.0f;
        alGetSourcef(mStream, AL_ROLLOFF_FACTOR, &mitigation);
        return static_cast<int>(mitigation * 100);
    }
}
