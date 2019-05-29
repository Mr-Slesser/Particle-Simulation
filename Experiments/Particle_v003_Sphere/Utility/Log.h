#ifndef LOGGING_H
#define LOGGING_H

#include <memory>

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define CORE_LOG_TRACE(...)  ::PT::Log::getCore()->trace(__VA_ARGS__);
#define CORE_LOG_INFO(...)   ::PT::Log::getCore()->info(__VA_ARGS__);
#define CORE_LOG_WARN(...)   ::PT::Log::getCore()->warn(__VA_ARGS__);
#define CORE_LOG_ERROR(...)  ::PT::Log::getCore()->error(__VA_ARGS__);
#define CORE_LOG_CRITICAL(...)  ::PT::Log::getCore()->critical(__VA_ARGS__);

#define GL_LOG_TRACE(...)   ::PT::Log::getGL()->trace(__VA_ARGS__);
#define GL_LOG_INFO(...)    ::PT::Log::getGL()->info(__VA_ARGS__);
#define GL_LOG_WARN(...)    ::PT::Log::getGL()->warn(__VA_ARGS__);
#define GL_LOG_ERROR(...)   ::PT::Log::getGL()->error(__VA_ARGS__);
#define GL_LOG_CRITICAL(...)   ::PT::Log::getGL()->critical(__VA_ARGS__);

// Disable for non-debug.
#ifdef NDEBUG
    #define CORE_LOG_TRACE
    #define CORE_LOG_INFO
    #define CORE_LOG_WARN
    #define CORE_LOG_ERROR
    #define CORE_LOG_CRITICAL

    #define GL_LOG_TRACE
    #define GL_LOG_INFO
    #define GL_LOG_WARN
    #define GL_LOG_ERROR
    #define GL_LOG_CRITICAL
#endif

namespace PT
{
    class Log
    {
    private:
        static std::shared_ptr<spdlog::logger> core;
        static std::shared_ptr<spdlog::logger> gl;
        
    public:
        static void init();

        inline static std::shared_ptr<spdlog::logger>& getCore() { return core; }
        inline static std::shared_ptr<spdlog::logger>& getGL() { return gl; }
    };
    
} // namespace PT


#endif /* LOGGING_H */
