#include <AudioEngine.h>

int main(int argc, char** argv)
{
    AudioEngine::AudioPlayer player;
    
    if (argc < 2)
    {
        std::cerr << "Any audio is requested" << std::endl;
        return 1;
    }
    AudioEngine::AudioBuffer audioBuffer(argv[1]);
    
    AudioEngine::AudioStream audioStream(audioBuffer);
    
    player.addStream(audioStream.getStream());
    player.playStream(audioStream.getStream());
    
    while(player.isRunningAudio())
    {
        player.updateSwaps();
    }

    return 0;
}