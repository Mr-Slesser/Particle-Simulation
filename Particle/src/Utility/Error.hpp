#ifndef ERROR_HPP
#define ERROR_HPP

#include <string.h>
#include <stdio.h>
#include <functional>

#include "Exception.hpp"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define FATALF(t, msg, fn) Error::Fatal(t, msg, __FILENAME__, __LINE__, fn)
#define FATAL(t, msg) Error::Fatal(t, msg, __FILENAME__, __LINE__)

namespace Error
{
    // TODO: Error type as str?
    enum TYPE
    {
        WINDOW_CREATION_FAIL    = 0x0001,
        WINDOW_GLAD_FAIL        = 0x0002,
        PROGRAM_SHADER_LOAD     = 0x0010,
        PROGRAM_SHADER_COMPILE  = 0x0011,
        PROGRAM_SHADER_LINK     = 0x0012
    };

    static void Fatal(
        TYPE t, 
        const char* msg = "No message",
        const char* file = nullptr,
        const int line = 0,
        std::function<void()> on_exit = {})
    {   
        printf("ERROR::%d: %s (%d: %s)\n", t, msg, line, file);
        if (on_exit) on_exit();
        glfwTerminate();
        exit(-1);
    }

} // Error

#endif /* ERROR_HPP */
