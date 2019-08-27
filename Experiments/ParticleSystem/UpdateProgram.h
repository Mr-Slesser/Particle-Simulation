#ifndef UPDATEPROGRAM_H
#define UPDATEPROGRAM_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

#include "../GL/GL_Helpers.hpp"
#include "../Utility/Error.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VS_UPDATE "./Particle/Resources/Shaders/update.vertex"
#define FS_UPDATE "./Particle/Resources/Shaders/update.fragment"
#define GS_UPDATE "./Particle/Resources/Shaders/update.geometry"

namespace PT
{
    #define MAX_PARTICLES 1000
    #define PARTICLE_LIFETIME 10.0f

    #define PARTICLE_TYPE_LAUNCHER 0.0f
    #define PARTICLE_TYPE_SHELL 1.0f
    #define PARTICLE_TYPE_SECONDARY_SHELL 2.0f

    class UpdateProgram
    {
    private:
        unsigned int ID;

    public:
        UpdateProgram(const char* vertexPath = VS_UPDATE, const char* fragmentPath = FS_UPDATE, const char* geomPath = GS_UPDATE);
        virtual ~UpdateProgram();

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
} // PT

#endif /* UPDATEPROGRAM_H */