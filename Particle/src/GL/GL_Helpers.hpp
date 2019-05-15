#ifndef GL_HELPERS_HPP
#define GL_HELPERS_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <fstream>
#include <vector>

#include "../Utility/Error.hpp"

namespace GL
{
    static void compileShader(const char* filePath, int& id)
    {
        std::ifstream shaderFile(filePath);
        
        if (shaderFile.fail())
        {
            FATAL(Error::TYPE::PROGRAM_SHADER_LOAD, strerror(errno));
        }

        std::string fileContents;
        std::string line;
        
        while(std::getline(shaderFile, line))
        {
            fileContents += line + "\n";
        }

        shaderFile.close();
        const char* contentsPtr = fileContents.c_str();
        glShaderSource(id, 1, &contentsPtr, nullptr);
        glCompileShader(id);
        int success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        
        if(!success)
        {
            GLint length = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)alloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            glDeleteShader(id); 
            FATAL(Error::TYPE::PROGRAM_SHADER_COMPILE, message);
        }
    }

} // GL

#endif /* GL_HELPERS_HPP */
