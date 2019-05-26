#ifndef UPDATEPROGRAM_H
#define UPDATEPROGRAM_H

#include "OpenGL.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VS_UPDATE "./Particle/Resources/Shaders/update.vertex"

namespace GL
{
    class UpdateProgram
    {
    private:
        unsigned int ID;
        std::map<const char*, int> uniform_locations;
        bool compileShader(const char* filePath, int& id);

    public:
        UpdateProgram();
        virtual ~UpdateProgram();

        bool init(const char* vertexPath = VS_UPDATE);

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