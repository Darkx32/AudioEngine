# AudioEngine
AudioEngine is a library made in C++, using **FFMPEG** and **OpenAL**. It consists of facilitating the handling of audio files for future applications.
It is in its first version, it may present bugs or failures, but until then, I will try to adjust it every day.
* Play any audio file (WAVE, OGG, MP3, ...).
* Easy to use.
* Modern libraries and versions.

## How compile
* Install and configure [vcpkg](https://github.com/microsoft/vcpkg), following instructions from repository.
* Add the vcpkg root folder to the **VCPKG_ROOT** environment variable.
* Install FFMPEG and OpenAL in vcpkg, following these commands:
```bash
./vcpkg install ffmpeg
./vcpkg install openal-soft
```
* Clone this repository and build using CMake.
```bash
git clone https://github.com/Darkx32/AudioEngine.git
cd AudioEngine
cmake .
cmake --build .
```
* Run example in output folder.

## Example code
```c++
#include <AudioEngine/AudioEngine.h> // Import AudioEngine library

int main(int argc, char** argv)
{
    AudioEngine::AudioPlayer player; // Create player sound
    AudioEngine::AudioBuffer audioBuffer("<sound_file>"); // Create new audio buffer from file
    AudioEngine::AudioStream audioStream(audioBuffer); // Create the stream from audio buffer
    
    player.addStream(audioStream.getStream()); // Add stream to play
    player.playStream(audioStream.getStream()); // Play stream
    
    while(player.isRunningAudio()) // Detect if any sound is playing
    {
        player.updateSwaps(); // Player update
    }

    return 0;
}
```

## To-do list Project

- [X] Audio control and management.
- [X] Play any file song.
- [X] Set volume and position.
- [ ] Filter and reverb audio streams
- [ ] Use microphone
