#include "AudioEngine/tools.hpp"
#include <iostream>
#include <cstdio>
#include <cstdarg>
#include <AL/al.h>

static int log_level_g = 3;

namespace AudioEngine
{
    constexpr auto RESET = "\033[0m";
    constexpr auto RED = "\033[31m";
    constexpr auto YELLOW = "\033[33m";
    constexpr auto CYAN = "\033[36m";

    void hasOpenALError(unsigned int* error) {
        if ((*error = alGetError()) != AL_NO_ERROR)
        {
            const char* err = getErrorByOpenAL(static_cast<int>(*error));
            logger(LOG_ERROR, err);
        }
    }

    /**
     * Set the log level
     * @param newLogLevel New log level
     */
    void setLogLevel(const int newLogLevel)
    {
        log_level_g = newLogLevel;
    }

    /**
     * Get the log level
     * @return Log level
     */
    int getLogLevel()
    {
        return log_level_g;
    }

    /**
     * Log a message
     * @param logLevel Level for log
     * @param msg Message to be logged
     * @param ... Parameters
     */
    void logger(const int logLevel, const char* msg, ...)
    {
        va_list args;
        va_start(args, msg);

        char buffer[1024];
        int _ = vsnprintf(buffer, sizeof(buffer), msg, args);

        if (log_level_g < logLevel)
            return;

        switch (logLevel)
        {
        case LOG_INFO: // Log color cyan for simple LOG
            std::clog << CYAN << "[INFO] " << buffer << RESET << "\n";
            break;

        case LOG_WARN: // Log color yellow for warning LOG
            std::clog << YELLOW << "[WARN] " << buffer << RESET << "\n";
            break;

        case LOG_ERROR: // Log color red for error LOG
            std::cerr << RED << "[ERROR] " << buffer << RESET << "\n";
            break;

        default:
            break;
        }

        va_end(args);
    }

    /**
     * Get the error by OpenAL
     * @param error Error code from OpenAL
     * @return decode error from code by OpenAL
     */
    const char* getErrorByOpenAL(const int error)
    {
        switch (error)
        {
        case AL_INVALID_NAME:      return "OPENAL: Invalid name";
        case AL_INVALID_ENUM:      return "OPENAL: Invalid enum";
        case AL_INVALID_VALUE:     return "OPENAL: Invalid value";
        case AL_INVALID_OPERATION: return "OPENAL: Invalid operation";
        case AL_OUT_OF_MEMORY:     return "OPENAL: Out of memory";
        default:                   return "OPENAL: Unknown";
        }
    }
}
