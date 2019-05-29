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

    void GC::init() {
        // Add values..
        addInt("MAX_PARTICLES", 1000000);
        addInt("CURR_NO_PARTICLES", 0);

        addBool("PAUSED", false);
        addBool("GUI_HOVER", false);

        glm::vec4 clear = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
        addVec4("CLEAR_COLOR", clear);
    }

    int& GC::getInt(const char* name)
    {
        if (ints.find(name) != ints.end())
        {
            return ints[name];
        }
        else
        {
            throw("getInt -> Name not found");
        }
    }

    float& GC::getFloat(const char* name)
    {
        if (floats.find(name) != floats.end())
        {
            return floats[name];
        }
        else
        {
            throw("getFloat -> Name not found");
        }
    }
    
    bool& GC::getBool(const char* name)
    {
        if (bools.find(name) != bools.end())
        {
            return bools[name];
        }
        else
        {
            throw("getBool -> Name not found");
        }
    }
    
    glm::vec4& GC::getVec4(const char* name)
    {
        if (vec4s.find(name) != vec4s.end())
        {
            return vec4s[name];
        }
        else
        {
            throw("getVec4 -> Name not found");
        }
    }

    bool GC::addInt(const char* name, int value)
    {
        if (ints.find(name) == ints.end())
        {
            ints[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

    bool GC::addFloat(const char* name, float value)
    {
        if (floats.find(name) == floats.end())
        {
            floats[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

    bool GC::addBool(const char* name, bool value)
    {
        if (bools.find(name) == bools.end())
        {
            bools[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

    bool GC::addVec4(const char* name, glm::vec4& value)
    {
        if (vec4s.find(name) == vec4s.end())
        {
            vec4s[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

    bool GC::updateInt(const char* name, int value)
    {
        if (ints.find(name) != ints.end())
        {
            ints[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

    bool GC::updateFloat(const char* name, float value)
    {
        if (floats.find(name) != floats.end())
        {
            floats[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

    bool GC::updateBool(const char* name, bool value)
    {
        if (bools.find(name) != bools.end())
        {
            bools[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

    bool GC::updateVec4(const char* name, glm::vec4& value)
    {
        if (vec4s.find(name) != vec4s.end())
        {
            vec4s[name] = value;
            return true;
        }
        else
        {  
            return false;
        }
    }

} // namespace PT
