#include "PCHeader.h"
#include "UpdateProgram.h"

GL::UpdateProgram::UpdateProgram()
{
}

GL::UpdateProgram::~UpdateProgram()
{
}

bool GL::UpdateProgram::init(const char *vertexPath, const char *fragmentPath)
{
    GL_LOG_TRACE("Starting update program init.");

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    if (!compileShader(vertexPath, vertexShader))
    {
        return false;
    }
    ID = glCreateProgram();
    GLCheck(glAttachShader(ID, vertexShader));

    const GLchar *feedbackVaryings[] = {"outPosition", "outColor"};
    glTransformFeedbackVaryings(ID, 2, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

    GLCheck(glLinkProgram(ID));

    int success = 0;
    char *infolog;
    GLCheck(glGetProgramiv(ID, GL_LINK_STATUS, &success));
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infolog);
        GL_LOG_CRITICAL("{}", infolog);
        return false;
    }
    GLCheck(glDeleteShader(vertexShader));

    GL_LOG_TRACE("UpdateProgram created with id: {}", ID);

    return true;
}

bool GL::UpdateProgram::generateShader(const char *filePath, int &id)
{
    std::ifstream shaderFile(filePath);

    if (shaderFile.fail())
    {
        GL_LOG_CRITICAL("[{}]{}: Could not load file {} ({})", __FILE__, __LINE__, filePath, strerror(errno));
        return false;
    }

    std::string contents[2];
    std::string line;
    int i;

    while (std::getline(shaderFile, line))
    {
        if (line.find("##::") != std::string::npos)
        {
            if (line.find("func") != std::string::npos)
            {
                i = 0;
            }
            else if (line.find("main") != std::string::npos)
            {
                i = 1;
            }
        }
        else
        {
            contents[i] += line + "\n";
        }
    }

    shaderFile.close();

    // Not we insert between pre defined stuff..
    // TODO: Have the bulk of this in an external file to load?
    std::string shaderSource = "";
    shaderSource += "#version 330 core\n";
    shaderSource += "layout (location = 0) in vec3 aPos;\n";
    shaderSource += "layout (location = 1) in vec4 aColor;\n";
    shaderSource += "out vec3 outPosition;\n";
    shaderSource += "out vec4 outColor;\n";
    shaderSource += "uniform float dt;\n";
    shaderSource += contents[0];
    shaderSource += "\nvoid main()\n";
    shaderSource += "{\n";
    shaderSource += contents[1];
    shaderSource += "\n}\n";

    const char *contentsPtr = shaderSource.c_str();
    GLCheck(glShaderSource(id, 1, &contentsPtr, nullptr));
    GLCheck(glCompileShader(id));
    int success = 0;
    GLCheck(glGetShaderiv(id, GL_COMPILE_STATUS, &success));

    if (!success)
    {
        GLint length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char *message = (char *)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        GL_LOG_CRITICAL("{}", message);
        GLCheck(glDeleteShader(id);) return false;
    }

    return true;
}