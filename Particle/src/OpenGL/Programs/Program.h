#ifndef PROGRAM_H
#define PROGRAM_H

#include "../OpenGL.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VS_BASIC "./Particle/Resources/Shaders/point.vertex"
#define FS_BASIC "./Particle/Resources/Shaders/point.fragment"

namespace GL
{
    class Program
    {
    protected:
        unsigned int ID;
        std::map<const char*, int> uniform_locations;
        virtual bool compileShader(const char* filePath, int& id);

    public:
        Program();
        virtual ~Program();

        virtual bool init(const char* vertexPath = VS_BASIC, const char* fragmentPath = FS_BASIC);

        void use();

        unsigned int getID() const { return ID; }
        int getUniformLocation(const char* name);

        // SECTION: Uniform helper functions.
        void setBool(const char* name, bool value);
        void setInt(const char* name, int value);
        void setFloat(const char* name, float value);
        void setVec2(const char* name, const glm::vec2 &value);
        void setVec2(const char* name, float x, float y);
        void setVec3(const char* name, const glm::vec3 &value);
        void setVec3(const char* name, float x, float y, float z);
        void setVec4(const char* name, const glm::vec4 &value);
        void setVec4(const char* name, float x, float y, float z, float w);
        void setMat2(const char* name, const glm::mat2 &mat);
        void setMat3(const char* name, const glm::mat3 &mat);
        void setMat4(const char* name, const glm::mat4 &mat);
    };
} // GL

#endif /* PROGRAM_H */
