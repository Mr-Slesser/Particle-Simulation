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
        std::ifstream vertexFile(filePath);
        
        if (vertexFile.fail())
        {
            FATALF(Error::TYPE::PROGRAM_SHADER_LOAD, strerror(errno), []() { printf("This is optional\n"); });
        }

        std::string fileContents;
        std::string line;
        
        while(std::getline(vertexFile, line))
        {
            fileContents += line + "\n";
        }

        vertexFile.close();
        const char* contentsPtr = fileContents.c_str();
        glShaderSource(id, 1, &contentsPtr, nullptr);
        glCompileShader(id);
        int success = 0;
        glGetShaderiv(id, GL_COMPILE_STATUS, &success);
        
        if(!success)
        {
            GLint maxLength = 0;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);
            std::vector<char> errorLog(maxLength);
            // TODO: Can I get rid of trailing '\n'?
            glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);
            glDeleteShader(id); 
            FATAL(Error::TYPE::PROGRAM_SHADER_COMPILE, &(errorLog[0]));
        }
    }

} // GL

#endif /* GL_HELPERS_HPP */
