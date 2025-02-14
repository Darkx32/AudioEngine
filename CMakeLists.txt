cmake_minimum_required(VERSION 3.11)

project(AudioEngine VERSION 1.0.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

add_subdirectory(libs/openal-soft)

add_library(AudioEngine SHARED)
target_sources(AudioEngine PRIVATE src/AudioBuffer.cpp src/AudioStream.cpp src/AudioPlayer.cpp src/tools.cpp)
target_include_directories(AudioEngine PUBLIC include)

target_link_libraries(AudioEngine OpenAL)