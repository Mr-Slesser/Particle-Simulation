#ifndef ERROR_HPP
#define ERROR_HPP

#include <string.h>
#include <cstring>
#include <stdio.h>
#include <functional>

#include "Exception.hpp"

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define FATALF(t, msg, fn) Error::Fatal(t, msg, __FILENAME__, __LINE__, fn)
#define FATAL(t, msg) Error::Fatal(t, msg, __FILENAME__, __LINE__)

#define ERROR_DEFINITION_FILE "../../Resources/Definitions/Error.def"

namespace Error
{
    enum TYPE
    {
        #define ERROR_DEF(x,y) x = y,
        #include ERROR_DEFINITION_FILE
        #undef ERROR_DEF
    };
    
    static inline char* enum_print(TYPE e) {
        // TODO: Make this a bit more elegant
        std::string r = "";
        switch (e) {
            #define ERROR_DEF(x,y) case y: r = #x;break;
            #include ERROR_DEFINITION_FILE
            #undef ERROR_DEF
            default: r = "Unknown";
        }

        char* c;
        strcpy(c, r.c_str());
        return c;
    }

    static void Fatal(
        TYPE t, 
        const char* msg = "No message",
        const char* file = nullptr,
        const int line = 0,
        std::function<void()> on_exit = {})
    {   
        printf("ERROR::%s: %s (%d: %s)\n", Error::enum_print(t), msg, line, file);
        if (on_exit) on_exit();
        glfwTerminate();
        exit(-1);
    }

} // Error

#endif /* ERROR_HPP */
