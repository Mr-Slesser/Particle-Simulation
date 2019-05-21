#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include "OpenGL.h"

#include <iostream>
#include <string>

#include "GL_Helpers.hpp"
#include "../Utility/Error.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VS_BASIC "./Particle/Resources/Shaders/basic.vertex"
#define FS_BASIC "./Particle/Resources/Shaders/basic.fragment"

// TODO: Uniform locations: register and add to map to stop constant lookups.

namespace GL
{
    class GLSLProgram
    {
    private:
        unsigned int ID;

    public:
        GLSLProgram(const char* vertexPath = VS_BASIC, const char* fragmentPath = FS_BASIC);
        virtual ~GLSLProgram();

        void use();
        void unuse();

        unsigned int getID() const { return ID; }

        // SECTION: Uniform helper functions.
        void setInt(const char* name, int value) const;
        void setFloat(const char* name, float value) const;
        void setInt2(const char* name, const glm::ivec2& values) const;
        void setInt2(const char* name, const int& x, const int& y) const;
        void setFloat2(const char* name, const glm::vec2& values) const;
        void setFloat2(const char* name, const float& x, const float& y) const;
        void setInt3(const char* name, const glm::ivec3& values) const;
        void setInt3(const char* name, const int& x, const int& y, const int& z) const;
        void setFloat3(const char* name, const glm::vec3& values) const;
        void setFloat3(const char* name, const float& x, const float& y, const float& z) const;
        void setInt4(const char* name, const glm::ivec4& values) const;
        void setInt4(const char* name, const int& x, const int& y, const int& z, const int& w) const;
        void setFloat4(const char* name, const glm::vec4& values) const;
        void setFloat4(const char* name, const float& x, const float& y, const float& z, const float& w) const;
        void setMat4x4f(const char* name, const glm::mat4& values);
    };
} // GL

#endif /* GLSLPROGRAM_H */
