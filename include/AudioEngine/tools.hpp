#pragma once

namespace AudioEngine
{
    static void RELEASE(const void* pointer) {
        if (pointer)
            delete pointer;
    }

    enum LOG_TYPE{
        LOG_QUIET = 0,
        LOG_INFO,
        LOG_WARN,
        LOG_ERROR
    };

    void hasOpenALError(unsigned int* error);
    void setLogLevel(int newLogLevel);
    int getLogLevel();
    void logger(const char* msg, int logLevel = LOG_INFO);

    const char* getErrorByOpenAL(int error);
}