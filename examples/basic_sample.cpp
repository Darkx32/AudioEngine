#include <AudioEngine.h>
#include <iostream>

int main(int argc, char** argv)
{
    AudioEngine::AudioPlayer player;

    AudioEngine::AudioBuffer audioBuffer(argv[1]);

    AudioEngine::AudioStream audioStream(audioBuffer);

    player.addStream(audioStream.getStream());
    player.playStream(audioStream.getStream());

    while (player.isRunningAudio())
    {
        player.updateSwaps();
    }

    return 0;
}