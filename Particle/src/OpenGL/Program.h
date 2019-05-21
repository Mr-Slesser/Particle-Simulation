#ifndef PROGRAM_H
#define PROGRAM_H

#include "OpenGL.h"

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

#include "../Utility/Error.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VS_BASIC "./Particle/Resources/Shaders/basic.vertex"
#define FS_BASIC "./Particle/Resources/Shaders/basic.fragment"

// TODO: Uniform locations: register and add to map to stop constant lookups.

namespace GL
{
    class Program
    {
    private:
        unsigned int ID;

        void compileShader(const char* filePath, int& id);

    public:
        Program(const char* vertexPath = VS_BASIC, const char* fragmentPath = FS_BASIC);
        virtual ~Program();

        void use();

        unsigned int getID() const { return ID; }

        // SECTION: Uniform helper functions.
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;
        void setVec2(const std::string &name, const glm::vec2 &value) const;
        void setVec2(const std::string &name, float x, float y) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const;
        void setVec4(const std::string &name, const glm::vec4 &value) const;
        void setVec4(const std::string &name, float x, float y, float z, float w);
        void setMat2(const std::string &name, const glm::mat2 &mat) const;
        void setMat3(const std::string &name, const glm::mat3 &mat) const;
        void setMat4(const std::string &name, const glm::mat4 &mat) const;
    };
} // GL

#endif /* PROGRAM_H */
