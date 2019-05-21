#include "Program.h"

GL::Program::Program(const char* vertexPath, const char* fragmentPath)
    : ID(0)
{
    // Vertex Shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexPath, vertexShader);

	// Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentPath, fragmentShader);

	// Link Shaders
	ID = glCreateProgram();
	GLCheck(glAttachShader(ID, vertexShader));
	GLCheck(glAttachShader(ID, fragmentShader));

	GLCheck(glLinkProgram(ID));

    // Check for linking errors
    int success = 0;
    char* infolog;
	GLCheck(glGetProgramiv(ID, GL_LINK_STATUS, &success));
	if (!success) {
		GLCheck(glGetProgramInfoLog(ID, 512, NULL, infolog));
        FATAL(Error::TYPE::PROGRAM_SHADER_LINK, infolog);
	}

	GLCheck(glDeleteShader(vertexShader));
	GLCheck(glDeleteShader(fragmentShader));
}

GL::Program::~Program()
{
    GLCheck(glDeleteProgram(ID));
}

void GL::Program::use()
{
    GLCheck(glUseProgram(ID));
}

void GL::Program::compileShader(const char* filePath, int& id)
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
    GLCheck(glShaderSource(id, 1, &contentsPtr, nullptr));
    GLCheck(glCompileShader(id));
    int success = 0;
    GLCheck(glGetShaderiv(id, GL_COMPILE_STATUS, &success));
    
    if(!success)
    {
        GLint length = 0;
        GLCheck(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCheck(glGetShaderInfoLog(id, length, &length, message));
        GLCheck(glDeleteShader(id);) 
        FATAL(Error::TYPE::PROGRAM_SHADER_COMPILE, message);
    }
}

// SECTION: Uniform Helper Functions
void GL::Program::setBool(const std::string &name, bool value) const
{         
    GLCheck(glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);) 
}
// ------------------------------------------------------------------------
void GL::Program::setInt(const std::string &name, int value) const
{ 
    GLCheck(glUniform1i(glGetUniformLocation(ID, name.c_str()), value);) 
}
// ------------------------------------------------------------------------
void GL::Program::setFloat(const std::string &name, float value) const
{ 
    GLCheck(glUniform1f(glGetUniformLocation(ID, name.c_str()), value);) 
}
// ------------------------------------------------------------------------
void GL::Program::setVec2(const std::string &name, const glm::vec2 &value) const
{ 
    GLCheck(glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);) 
}
void GL::Program::setVec2(const std::string &name, float x, float y) const
{ 
    GLCheck(glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);) 
}
// ------------------------------------------------------------------------
void GL::Program::setVec3(const std::string &name, const glm::vec3 &value) const
{ 
    GLCheck(glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);) 
}
void GL::Program::setVec3(const std::string &name, float x, float y, float z) const
{ 
    GLCheck(glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);) 
}
// ------------------------------------------------------------------------
void GL::Program::setVec4(const std::string &name, const glm::vec4 &value) const
{ 
    GLCheck(glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);) 
}
void GL::Program::setVec4(const std::string &name, float x, float y, float z, float w) 
{ 
    GLCheck(glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);) 
}
// ------------------------------------------------------------------------
void GL::Program::setMat2(const std::string &name, const glm::mat2 &mat) const
{
    GLCheck(glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void GL::Program::setMat3(const std::string &name, const glm::mat3 &mat) const
{
    GLCheck(glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}
// ------------------------------------------------------------------------
void GL::Program::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    GLCheck(glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]));
}