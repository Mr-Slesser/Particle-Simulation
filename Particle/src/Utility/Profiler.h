#ifndef PROFILER_H
#define PROFILER_H

using namespace std;
#define _PROFILER_FILE_LOG 1
#define _PROFILER_ON 1

#define OUTPUT "profiler-output-aftermesh"

#ifdef _PROFILER_FILE_LOG
#define _PROFILER_FILE_LOGGER
#else
#undef _PROFILER_FILE_LOGGER
#endif //  _LOG_TO_FILE

#if _PROFILER_ON
#define PROFILE(comments) profiler _pfinstance(comments)
#define PROFILE_FUNCTION profiler _pfinstance(__FUNCTION__)
#else
#define PROFILE(comments)
#define PROFILE_FUNCTION
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
        ss << OUTPUT << ".csv";
        logfile.open(ss.str(), ios::app);
        logfile << stream.str();
        logfile.close();
#else
        std::cout << stream.str();
#endif
    }
};

#endif /* PROFILER_H */
