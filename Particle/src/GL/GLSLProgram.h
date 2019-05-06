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
        unsigned int ID;

    public:
        GLSLProgram(const char* vertexPath = VS_BASIC, const char* fragmentPath = FS_BASIC);
        ~GLSLProgram();

        void use();
        void unuse();

        // SECTION: Uniform helper functions.

        // 1 Value
        void setInt(const char* name, int value) const;
        void setUInt(const char* name, unsigned int value) const;
        void setFloat(const char* name, float value) const;
        // Vectors: 2 Values
        void setInt2(const char* name, const int values[2]) const;
        void setInt2(const char* name, const int& x, const int& y) const;
        void setUInt2(const char* name, const unsigned int values[2]) const;
        void setUInt2(const char* name, const unsigned int& x, const unsigned int& y) const;
        void setFloat2(const char* name, const float values[2]) const;
        void setFloat2(const char* name, const float& x, const float& y) const;
        // Vectors: 3 Values
        void setInt3(const char* name, const int values[3]) const;
        void setInt3(const char* name, const int& x, const int& y, const int& z) const;
        void setUInt3(const char* name, const unsigned int values[3]) const;
        void setUInt3(const char* name, const unsigned int& x, const unsigned int& y, const unsigned int& z) const;
        void setFloat3(const char* name, const float values[3]) const;
        void setFloat3(const char* name, const float& x, const float& y, const float& z) const;

        // Vectors: 4 Values
        void setInt4(const char* name, const int values[4]) const;
        void setInt4(const char* name, const int& x, const int& y, const int& z, const int& w) const;
        void setUInt4(const char* name, const unsigned int values[4]) const;
        void setUInt4(const char* name, const unsigned int& x, const unsigned int& y, const unsigned int& z, const unsigned int& w) const;
        void setFloat4(const char* name, const float values[4]) const;
        void setFloat4(const char* name, const float& x, const float& y, const float& z, const float& w) const;
    };
} // GL

#endif /* GLSLPROGRAM_H */
