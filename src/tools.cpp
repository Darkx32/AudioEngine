#include "AudioEngine/tools.hpp"
#include <iostream>
#include <AL/al.h>

int logLevel_g = 3;

namespace AudioEngine
{
    #define RESET "\033[0m"
    #define RED "\033[31m"
    #define YELLOW "\033[33m"
    #define CYAN "\033[36m"

    /**
     * Set the log level
     * @param newLogLevel New log level
     */
    void setLogLevel(int newLogLevel)
    {
        logLevel_g = newLogLevel;
    }

    /**
     * Get the log level
     * @return Log level
     */
    int getLogLevel()
    {
        return logLevel_g;
    }

    /**
     * Log a message
     * @param msg Message to be logged
     */
    void logger(const char *msg, int logLevel)
    {
        if (logLevel_g < logLevel)
            return;

        switch (logLevel)
        {
        case LOG_INFO: // Log color cyan for simple LOG
            std::clog << CYAN << "[INFO] " << msg << RESET << std::endl;
            break;

        case LOG_WARN: // Log color yellow for warning LOG
            std::clog << YELLOW << "[WARN] " << msg << RESET << std::endl;
            break;

        case LOG_ERROR: // Log color red for error LOG
            std::cerr << RED << "[ERROR] " << msg << RESET << std::endl;
            break;

        default:
            break;
        }
    }

    /**
     * Get the error by OpenAL
     * @param error Error code from OpenAL
     * @return decode error from code by OpenAL
     */
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
