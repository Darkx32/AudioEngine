#pragma once

namespace AudioEngine
{
    template <typename T>
    static void RELEASE(T*& pointer) {
        if (pointer) {
            delete pointer;
            pointer = nullptr;
        }
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
    void logger(int logLevel, const char* msg, ...);

    const char* getErrorByOpenAL(int error);
}