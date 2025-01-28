#include "tools.h"
#include <string>

namespace AudioEngine
{
    char* getMessage(int code)
    {
        char* msg = new char[sizeof(int)];

        std::memcpy(msg, &code, sizeof(int));

        return msg;
    }

    char *getMessage(short code)
    {
        char* msg = new char[sizeof(short)];

        std::memcpy(msg, &code, sizeof(short));

        return msg;
    }
}
