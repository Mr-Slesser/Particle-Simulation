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

} // namespace PT
