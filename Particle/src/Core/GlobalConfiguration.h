#ifndef GLOBALCONFIGURATION_H
#define GLOBALCONFIGURATION_H

#include <map>

#include <glm/glm.hpp>

#include "../OpenGL/OpenGL.h"

namespace PT
{
    class GC
    {
    private:
        static GC* instance;
        GC();

        std::map<const char*, int> ints;
        std::map<const char*, float> floats;
        std::map<const char*, bool> bools;

        std::map<const char*, glm::vec4> vec4s;

    public:
        virtual ~GC();
        static GC* get();
        void init();

        int& getInt(const char* name);
        float& getFloat(const char* name);
        bool& getBool(const char* name);

        glm::vec4& getVec4(const char* name);


        bool addInt(const char* name, int value);
        bool addFloat(const char* name, float value);
        bool addBool(const char* name, bool value);

        bool addVec4(const char* name, glm::vec4& value);

        bool updateInt(const char* name, int value);
        bool updateFloat(const char* name, float value);
        bool updateBool(const char* name, bool value);
        bool toggleBool(const char* name);

        bool updateVec4(const char* name, glm::vec4& value);
    };
} // namespace PT

#endif /* GLOBALCONFIGURATION_H */
