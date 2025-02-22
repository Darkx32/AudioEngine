#include "tools.h"
#include <iostream>
#include <AL/al.h>

int logLevel_g = 3;

namespace AudioEngine
{
    // Simple logger
    #define RESET "\033[0m"
    #define RED "\033[31m"
    #define YELLOW "\033[33m"
    #define CYAN "\033[36m"

    void setLogLevel(int newLogLevel)
    {
        logLevel_g = newLogLevel;
    }

    int getLogLevel()
    {
        return logLevel_g;
    }

    void logger(const char *msg, int logLevel)
    {
        if (logLevel_g < logLevel)
            return;

        switch (logLevel)
        {
        case LOG_INFO: // Log color cyan
            std::clog << CYAN << "[INFO] " << msg << RESET << std::endl;
            break;

        case LOG_WARN: // Log color yellow
            std::clog << YELLOW << "[WARN] " << msg << RESET << std::endl;
            break;

        case LOG_ERROR: // Log color red
            std::cerr << RED << "[ERROR] " << msg << RESET << std::endl;
            break;

        default:
            break;
        }
    }

    /** Simple OpenAL Error translate */
    const char* getErrorByOpenAL(int error)
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
