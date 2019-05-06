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
    // TODO: Error type as str.
    enum TYPE
    {
        PROGRAM_SHADER_LOAD,
        PROGRAM_SHADER_COMPILE,
        PROGRAM_SHADER_LINK
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
        exit(0);
    }

} // Error

#endif /* ERROR_HPP */
