#include "PCHeader.h"
#include "Program.h"

GL::Program::Program()
    : ID(0)
{
}

GL::Program::~Program()
{
    GLCheck(glDeleteProgram(ID));
}

bool GL::Program::init(const char *vertexPath, const char *fragmentPath)
{
    GL_LOG_TRACE("Starting program creation");

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);

    if (!compileShader(vertexPath, vertexShader))
    {
        return false;
    }

    int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    if (!compileShader(fragmentPath, fragmentShader))
    {
        return false;
    }

    ID = glCreateProgram();
    GLCheck(glAttachShader(ID, vertexShader));
    GLCheck(glAttachShader(ID, fragmentShader));
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
    GLCheck(glDeleteShader(fragmentShader));

    GL_LOG_TRACE("Program created with id: {}", ID);

    return true;
}

void GL::Program::use()
{
    GLCheck(glUseProgram(ID));
}

int GL::Program::getUniformLocation(const char *name)
{
    if (uniform_locations.find(name) != uniform_locations.end())
    {
        return uniform_locations[name];
    }
    else
    {
        int a = glGetUniformLocation(ID, name);
        uniform_locations[name] = a;
        return a;
    }
}

bool GL::Program::compileShader(const char *filePath, int &id)
{
    std::ifstream shaderFile(filePath);

    if (shaderFile.fail())
    {
        GL_LOG_CRITICAL("[{}]{}: Could not load file {} ({})", __FILE__, __LINE__, filePath, strerror(errno));
        return false;
    }

    std::string fileContents;
    std::string line;

    while (std::getline(shaderFile, line))
    {
        fileContents += line + "\n";
    }

    shaderFile.close();
    const char *contentsPtr = fileContents.c_str();
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

// SECTION: Uniform Helper Functions
void GL::Program::setBool(const char *name, bool value)
{
    GLCheck(glUniform1i(getUniformLocation(name), (int)value);)
}
// ------------------------------------------------------------------------
void GL::Program::setInt(const char *name, int value)
{
    GLCheck(glUniform1i(getUniformLocation(name), value);)
}
// ------------------------------------------------------------------------
void GL::Program::setFloat(const char *name, float value)
{
    GLCheck(glUniform1f(getUniformLocation(name), value);)
}
// ------------------------------------------------------------------------
void GL::Program::setVec2(const char *name, const glm::vec2 &value)
{
    GLCheck(glUniform2fv(getUniformLocation(name), 1, &value[0]);)
}
void GL::Program::setVec2(const char *name, float x, float y)
{
    GLCheck(glUniform2f(getUniformLocation(name), x, y);)
}
// ------------------------------------------------------------------------
void GL::Program::setVec3(const char *name, const glm::vec3 &value)
{
    GLCheck(glUniform3fv(getUniformLocation(name), 1, &value[0]);)
}
void GL::Program::setVec3(const char *name, float x, float y, float z)
{
    GLCheck(glUniform3f(getUniformLocation(name), x, y, z);)
}
// ------------------------------------------------------------------------
void GL::Program::setVec4(const char *name, const glm::vec4 &value)
{
    GLCheck(glUniform4fv(getUniformLocation(name), 1, &value[0]);)
}
void GL::Program::setVec4(const char *name, float x, float y, float z, float w)
{
    GLCheck(glUniform4f(getUniformLocation(name), x, y, z, w);)
}
// ------------------------------------------------------------------------
void GL::Program::setMat2(const char *name, const glm::mat2 &mat)
{
    GLCheck(glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void GL::Program::setMat3(const char *name, const glm::mat3 &mat)
{
    GLCheck(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void GL::Program::setMat4(const char *name, const glm::mat4 &mat)
{
    GLCheck(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}