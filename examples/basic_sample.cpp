#include <AudioEngine/AudioEngine.hpp>

int main(int argc, char** argv)
{
    AudioEngine::AudioPlayer player;
    
    if (argc < 2)
    {
        AudioEngine::logger(AudioEngine::LOG_ERROR, "Any audio is requested");
        return 1;
    }
    
    AudioEngine::AudioStream audioStream(argv[1]);
    
    player.playStream(audioStream.getStream());
    
    while(player.isRunningAudio())
    {
        player.updateSwaps();
    }

    return 0;
}