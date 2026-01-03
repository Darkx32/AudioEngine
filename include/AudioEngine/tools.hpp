#pragma once

namespace AudioEngine
{
	/**
	 * Release and clean the pointer
	 * @param pointer Any pointer
	 */
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

    /**
     * Get if exists error
     * @param error Change this to actual OpenAL error
     */
    void hasOpenALError(unsigned int* error);

    /**
     * Set the log level
     * @param newLogLevel New log level
     */
    void setLogLevel(int newLogLevel);

    /**
     * Get the log level
     * @return Log level
     */
    int getLogLevel();

    /**
     * Log a message
     * @param logLevel Level for log
     * @param msg Message to be logged
     * @param ... Parameters
     */
    void logger(int logLevel, const char* msg, ...);

    /**
     * Get the error by OpenAL
     * @param error Error code from OpenAL
     * @return decode error from code by OpenAL
     */
    const char* getErrorByOpenAL(int error);
}