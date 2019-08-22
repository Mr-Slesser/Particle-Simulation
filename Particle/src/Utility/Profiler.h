#ifndef PROFILER_H
#define PROFILER_H

//  Enablers from Outside
//  Use the below settings as a Compile Time Definition if you would like to profile.
#define _PROFILER_FILE_LOG 1

// Private Impl
#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>

#include "../Core/GlobalConfiguration.h"

using namespace std;
#ifdef _PROFILER_FILE_LOG
#define _PROFILER_FILE_LOGGER
#else
#undef _PROFILER_FILE_LOGGER
#endif //  _LOG_TO_FILE

#define RENDERER_FORWARD 1

#if RENDERER_FORWARD
#define OUTPUT "forward-profiler-output-"
#else
#define OUTPUT "naive-profiler-output-"
#endif

struct profiler
{
    std::string name;
    std::chrono::high_resolution_clock::time_point start;

    profiler(std::string const &n)
        : name(n), start(std::chrono::high_resolution_clock::now())
    {
    }

    ~profiler()
    {

        auto e = std::chrono::high_resolution_clock::now();
        auto s = std::chrono::time_point_cast<std::chrono::microseconds>(start).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(e).time_since_epoch().count();

        auto duration = end - s;
        double ms = duration * 0.001;

        std::stringstream stream;

        stream << name << ", "
               << duration << ", "
               << ms << '\n';

#ifdef _PROFILER_FILE_LOGGER
        ofstream logfile;
        std::stringstream ss;
        ss << OUTPUT << PT::GC::get()->getInt("MAX_PARTICLES") << ".csv";
        logfile.open(ss.str(), ios::app);
        logfile << stream.str();
        logfile.close();
#else
        std::cout << stream.str();
#endif
    }
};

//  Profiler Macros
//  Use this Macro to add CustomComments
#define PROFILE_FUNCTION_WITHCOMMENTS(comments) profiler _pfinstance(comments)
// By Default this macro will print the function name.
#define PROFILE_FUNCTION profiler _pfinstance(__FUNCTION__) //  GETS CALLING FN NAME, __LINE__ and __FILE__ also available.

// Example Usage
/*
int main()
{
    PROFILE_FUNCTION_WITHCOMMENTS("Main Function");
    PROFILE_FUNCTION;
}
*/
#endif /* PROFILER_H */
