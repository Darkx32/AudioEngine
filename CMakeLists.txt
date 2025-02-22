cmake_minimum_required(VERSION 3.31)

set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(BUILD_EXAMPLES True CACHE STRING "For build examples.")

project(AudioEngine VERSION 1.0.0)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

find_package(OpenAL CONFIG REQUIRED)
find_package(FFMPEG REQUIRED)

add_library(AudioEngine SHARED)
target_sources(AudioEngine PRIVATE src/AudioBuffer.cpp src/AudioStream.cpp src/AudioPlayer.cpp src/tools.cpp)
target_include_directories(AudioEngine PUBLIC include)

target_link_libraries(AudioEngine PRIVATE OpenAL::OpenAL)

target_link_directories(AudioEngine PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(AudioEngine PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(AudioEngine PRIVATE ${FFMPEG_LIBRARIES})

if(BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()
