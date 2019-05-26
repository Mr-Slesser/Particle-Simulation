#include "UpdateProgram.h"

GL::UpdateProgram::UpdateProgram()
    : ID(0)
{
}

GL::UpdateProgram::~UpdateProgram()
{
    GLCheck(glDeleteProgram(ID));
}

bool GL::UpdateProgram::init(const char* vertexPath)
{
    GL_LOG_TRACE("Starting update program init.");

    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    
    if(!compileShader(vertexPath, vertexShader))
    {
        return false;
    }
// GL_LOG_TRACE("A");
	ID = glCreateProgram();
	GLCheck(glAttachShader(ID, vertexShader));
// GL_LOG_TRACE("B");

    // const GLchar* feedbackVaryings[] = { "outValue" };
    // glTransformFeedbackVaryings(ID, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
    const GLchar* feedbackVaryings[] = { "outPosition", "outColor" };
    glTransformFeedbackVaryings(ID, 2, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);
// GL_LOG_TRACE("C");


	GLCheck(glLinkProgram(ID));
// GL_LOG_TRACE("D");

    int success = 0;
    char* infolog;
	GLCheck(glGetProgramiv(ID, GL_LINK_STATUS, &success));
	if (!success) {
		glGetProgramInfoLog(ID, 512, NULL, infolog);
        GL_LOG_CRITICAL("{}", infolog);
        return false;
	}
// GL_LOG_TRACE("E");
	GLCheck(glDeleteShader(vertexShader));
// GL_LOG_TRACE("F");

    GL_LOG_TRACE("UpdateProgram created with id: {}", ID);

    return true;
}

void GL::UpdateProgram::use()
{
    GLCheck(glUseProgram(ID));
}

int GL::UpdateProgram::getUniformLocation(const char* name)
{
    if (uniform_locations.find(name) != uniform_locations.end()) {
        return uniform_locations[name];
    } else {
        int a = glGetUniformLocation(ID, name);
        uniform_locations[name] = a;
        return a;
    }
}

bool GL::UpdateProgram::compileShader(const char* filePath, int& id)
{
    std::ifstream shaderFile(filePath);
        
    if (shaderFile.fail())
    {
        GL_LOG_CRITICAL("[{}]{}: Could not compile file {} ({})", __FILE__, __LINE__, filePath, strerror(errno));
        return false;
    }

    std::string fileContents;
    std::string line;
    
    while(std::getline(shaderFile, line))
    {
        fileContents += line + "\n";
    }

    shaderFile.close();
    const char* contentsPtr = fileContents.c_str();
    GLCheck(glShaderSource(id, 1, &contentsPtr, nullptr));
    GLCheck(glCompileShader(id));
    int success = 0;
    GLCheck(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    
    if(!success)
    {
        GLint length = 0;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        GL_LOG_CRITICAL("{}", message);
        GLCheck(glDeleteShader(id);) 
        return false;
    }

    return true;
}

// SECTION: Uniform Helper Functions
void GL::UpdateProgram::setBool(const char* name, bool value)
{         
    GLCheck(glUniform1i(getUniformLocation(name), (int)value);) 
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setInt(const char* name, int value)
{ 
    GLCheck(glUniform1i(getUniformLocation(name), value);) 
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setFloat(const char* name, float value)
{ 
    GLCheck(glUniform1f(getUniformLocation(name), value);) 
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setVec2(const char* name, const glm::vec2 &value)
{ 
    GLCheck(glUniform2fv(getUniformLocation(name), 1, &value[0]);) 
}
void GL::UpdateProgram::setVec2(const char* name, float x, float y)
{ 
    GLCheck(glUniform2f(getUniformLocation(name), x, y);) 
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setVec3(const char* name, const glm::vec3 &value)
{ 
    GLCheck(glUniform3fv(getUniformLocation(name), 1, &value[0]);) 
}
void GL::UpdateProgram::setVec3(const char* name, float x, float y, float z)
{ 
    GLCheck(glUniform3f(getUniformLocation(name), x, y, z);) 
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setVec4(const char* name, const glm::vec4 &value)
{ 
    GLCheck(glUniform4fv(getUniformLocation(name), 1, &value[0]);) 
}
void GL::UpdateProgram::setVec4(const char* name, float x, float y, float z, float w) 
{ 
    GLCheck(glUniform4f(getUniformLocation(name), x, y, z, w);) 
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setMat2(const char* name, const glm::mat2 &mat)
{
    GLCheck(glUniformMatrix2fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setMat3(const char* name, const glm::mat3 &mat)
{
    GLCheck(glUniformMatrix3fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void GL::UpdateProgram::setMat4(const char* name, const glm::mat4 &mat)
{
    GLCheck(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}