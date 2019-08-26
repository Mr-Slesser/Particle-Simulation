#include "PCHeader.h"
#include "Log.h"

// TODO: Log to file option.

namespace PT
{
std::shared_ptr<spdlog::logger> Log::core;
std::shared_ptr<spdlog::logger> Log::gl;

void Log::init()
{
    // [HH::MM::SS(MS)][Level] Name: Text
    spdlog::set_pattern("%^[%T(%e)][%l] %n: %v%$");

    core = spdlog::stdout_color_mt("CORE");
    core->set_level(spdlog::level::trace);

    gl = spdlog::stdout_color_mt("GL");
    gl->set_level(spdlog::level::trace);
}
} // namespace PT
