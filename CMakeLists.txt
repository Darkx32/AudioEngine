cmake_minimum_required(VERSION 3.20)

if (LINUX)
	set(CMAKE_SHARED_LINKER_FLAGS "-Wl,-Bsymbolic")
endif()
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)

option(AUDIOENGINE_EXAMPLES "Build examples" ON)

include(GNUInstallDirs)

project(AudioEngine VERSION 1.0)

enable_language(CXX)

find_package(OpenAL CONFIG REQUIRED)
find_package(FFMPEG REQUIRED)

add_library(AudioEngine SHARED)
target_sources(AudioEngine PRIVATE src/AudioBuffer.cpp src/AudioStream.cpp src/AudioPlayer.cpp src/tools.cpp)
target_include_directories(AudioEngine
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(AudioEngine PRIVATE OpenAL::OpenAL)

target_link_directories(AudioEngine PRIVATE ${FFMPEG_INCLUDE_DIRS})
target_link_directories(AudioEngine PRIVATE ${FFMPEG_LIBRARY_DIRS})
target_link_libraries(AudioEngine PRIVATE ${FFMPEG_LIBRARIES})

install(
    TARGETS AudioEngine
    EXPORT AudioEngineTargets
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp"
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/AudioEngineConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/AudioEngineConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/AudioEngine
)

install(
    EXPORT AudioEngineTargets
    FILE AudioEngineTargets.cmake
    NAMESPACE AudioEngine::
    DESTINATION ${CMAKE_INSTALL_DATADIR}/AudioEngine
)

install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/AudioEngineConfig.cmake"
    DESTINATION ${CMAKE_INSTALL_DATADIR}/AudioEngine
)

if(AUDIOENGINE_EXAMPLES)
    add_subdirectory(examples)
endif()