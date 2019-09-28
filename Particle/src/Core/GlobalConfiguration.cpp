#include "PCHeader.h"
#include "GlobalConfiguration.h"

namespace PT
{
GC *GC::instance = 0;

GC *GC::get()
{
    if (!instance)
        instance = new GC;
    return instance;
}

GC::GC()
{
}

GC::~GC()
{
    ints.clear();
    floats.clear();
}

void GC::init()
{
    // Add values..
    addInt("MAX_PARTICLES", 1000000);
    addInt("CURR_NO_PARTICLES", 0);

    addBool("PAUSED", false);
    addBool("GUI_HOVER", false);

    glm::vec4 clear = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    addVec4("CLEAR_COLOR", clear);
}

int GC::getInt(const char *name)
{
    if (ints.find(name) != ints.end())
    {
        return ints[name];
    }
    else
    {
        CORE_LOG_ERROR("Global Config::getInt() -> {} not found.", name);
        return 0;
    }
}

float GC::getFloat(const char *name)
{
    if (floats.find(name) != floats.end())
    {
        return floats[name];
    }
    else
    {
        CORE_LOG_ERROR("Global Config::getFloat() -> {} not found.", name);
        return 0;
    }
}

bool GC::getBool(const char *name)
{
    if (bools.find(name) != bools.end())
    {
        return bools[name];
    }
    else
    {
        CORE_LOG_ERROR("Global Config::getBool() -> {} not found.", name);
        return 0;
    }
}

glm::vec4 GC::getVec4(const char *name)
{
    if (vec4s.find(name) != vec4s.end())
    {
        return vec4s[name];
    }
    else
    {
        CORE_LOG_ERROR("Global Config::getVec4() -> {} not found.", name);
        return glm::vec4(1.0f);
    }
}

bool GC::addInt(const char *name, int value)
{
    if (ints.find(name) == ints.end())
    {
        ints[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::addInt() -> Unable to add {} (value {})", name, value);
        return false;
    }
}

bool GC::addFloat(const char *name, float value)
{
    if (floats.find(name) == floats.end())
    {
        floats[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::addFloat() -> Unable to add {} (value {})", name, value);
        return false;
    }
}

bool GC::addBool(const char *name, bool value)
{
    if (bools.find(name) == bools.end())
    {
        bools[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::addBool() -> Unable to add {} (value {})", name, value);
        return false;
    }
}

bool GC::addVec4(const char *name, glm::vec4 &value)
{
    if (vec4s.find(name) == vec4s.end())
    {
        vec4s[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::addVec4() -> Unable to add {}", name);
        return false;
    }
}

bool GC::updateInt(const char *name, int value)
{
    if (ints.find(name) != ints.end())
    {
        ints[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::updateInt() -> Unable to update {} (value {})", name, value);
        return false;
    }
}

bool GC::updateFloat(const char *name, float value)
{
    if (floats.find(name) != floats.end())
    {
        floats[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::updateFloat() -> Unable to update {} (value {})", name, value);
        return false;
    }
}

bool GC::updateBool(const char *name, bool value)
{
    if (bools.find(name) != bools.end())
    {
        bools[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::updateBool() -> Unable to update {} (value {})", name, value);
        return false;
    }
}

bool GC::toggleBool(const char *name)
{
    if (bools.find(name) != bools.end())
    {
        bools[name] = !bools[name];
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::toggleBool() -> Unable to toggle {}", name);
        return false;
    }
}

bool GC::updateVec4(const char *name, glm::vec4 &value)
{
    if (vec4s.find(name) != vec4s.end())
    {
        vec4s[name] = value;
        return true;
    }
    else
    {
        CORE_LOG_WARN("Global Config::updateVec4() -> Unable to update {}", name);
        return false;
    }
}

} // namespace PT
