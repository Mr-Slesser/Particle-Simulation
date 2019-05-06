#ifndef GLSLPROGRAM_H
#define GLSLPROGRAM_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <string>

#include "GL_Helpers.hpp"
#include "../Utility/Error.hpp"

// TODO: Formalize the default shader files.
#define VS_BASIC "./Particle/Resources/Shaders/basic.vertex"
#define FS_BASIC "./Particle/Resources/Shaders/basic.fragment"

// TODO: Uniform locations: register and add to map to stop constant lookups.

namespace GL
{
    class GLSLProgram
    {
    private:
        unsigned int _id;

    public:
        GLSLProgram(const char* vertexPath = VS_BASIC, const char* fragmentPath = FS_BASIC);
        ~GLSLProgram();

        void use();

        // SECTION: Uniform helper functions.
        void setInt(const char* name, int value) const;
        void setUInt(const char* name, unsigned int value) const;
        void setBool(const char* name, bool value) const;
        void setFloat(const char* name, float value) const;
    };
} // GL

#endif /* GLSLPROGRAM_H */
