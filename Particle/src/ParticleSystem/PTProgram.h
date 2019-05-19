
#ifndef PTPROGRAM_H
#define PTPROGRAM_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

#include "../GL/GL_Helpers.hpp"
#include "../Utility/Error.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#define VS_RENDER "./Particle/Resources/Shaders/render.vertex"
#define FS_RENDER "./Particle/Resources/Shaders/render.fragment"

#define VS_UPDATE "./Particle/Resources/Shaders/update.vertex"
#define FS_UPDATE "./Particle/Resources/Shaders/update.fragment"

// TODO: Uniform locations: register and add to map to stop constant lookups.

namespace PT
{
    struct PTProgramArgs {
        int count;
        const char* vars[2];
    };

    class PTProgram
    {
    private:
        unsigned int ID;

    public:
        PTProgram(const char* vertexPath, const char* fragmentPath, int args);
        virtual ~PTProgram();

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

#endif /* PTPROGRAM_H */
