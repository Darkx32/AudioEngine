#include "tools.h"

#ifdef _WIN32
#include <string>
#endif

#ifdef linux
#include <cstring>
#endif

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
