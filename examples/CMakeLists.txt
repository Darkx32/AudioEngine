cmake_minimum_required(VERSION 3.14)

project(basic_sample)
add_executable(basic_sample basic_sample.cpp)

target_link_libraries(basic_sample PRIVATE AudioEngine)

project(loop_audio)
add_executable(loop_audio loop_audio.cpp)

target_link_libraries(loop_audio PRIVATE AudioEngine)