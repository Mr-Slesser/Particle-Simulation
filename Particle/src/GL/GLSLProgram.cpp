#include "GLSLProgram.h"

GL::GLSLProgram::GLSLProgram(const char* vertexPath, const char* fragmentPath)
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
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glLinkProgram(ID);

    // Check for linking errors
    int success = 0;
    char* infolog;
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
        ID = 0;
		glGetProgramInfoLog(ID, 512, NULL, infolog);
        FATAL(Error::TYPE::PROGRAM_SHADER_LINK, infolog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GL::GLSLProgram::~GLSLProgram()
{
    glDeleteProgram(ID);
}

void GL::GLSLProgram::use()
{
    glUseProgram(ID);
}

void GL::GLSLProgram::unuse()
{
    glUseProgram(0);
}

// SECTION: Uniform Helper Functions
void GL::GLSLProgram::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value); 
}

void GL::GLSLProgram::setUInt(const char* name, unsigned int value) const
{
    glUniform1ui(glGetUniformLocation(ID, name), value); 
}

void GL::GLSLProgram::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value); 
}

void GL::GLSLProgram::setInt2(const char* name, const int values[2]) const
{
    glUniform2iv(glGetUniformLocation(ID, name), 2, values); 
}

void GL::GLSLProgram::setInt2(const char* name, const int& x, const int& y) const
{
    glUniform2i(glGetUniformLocation(ID, name), x, y); 
}

void GL::GLSLProgram::setUInt2(const char* name, const unsigned int values[2]) const
{
    glUniform2uiv(glGetUniformLocation(ID, name), 2, values); 
}

void GL::GLSLProgram::setUInt2(const char* name, const unsigned int& x, const unsigned int& y) const
{
    glUniform2ui(glGetUniformLocation(ID, name), x, y); 
}

void GL::GLSLProgram::setFloat2(const char* name, const float values[2]) const
{
    glUniform2fv(glGetUniformLocation(ID, name), 2, values); 
}
void GL::GLSLProgram::setFloat2(const char* name, const float& x, const float& y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y); 
}

void GL::GLSLProgram::setInt3(const char* name, const int values[3]) const
{
    glUniform3iv(glGetUniformLocation(ID, name), 3, values); 
}

void GL::GLSLProgram::setInt3(const char* name, const int& x, const int& y, const int& z) const
{
    glUniform3i(glGetUniformLocation(ID, name), x, y, z); 
}

void GL::GLSLProgram::setUInt3(const char* name, const unsigned int values[3]) const
{
    glUniform3uiv(glGetUniformLocation(ID, name), 3, values); 
}

void GL::GLSLProgram::setUInt3(const char* name, const unsigned int& x, const unsigned int& y, const unsigned int& z) const
{
    glUniform3ui(glGetUniformLocation(ID, name), x, y, z); 
}

void GL::GLSLProgram::setFloat3(const char* name, const float values[3]) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 3, values); 
}

void GL::GLSLProgram::setFloat3(const char* name, const float& x, const float& y, const float& z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
}

void GL::GLSLProgram::setInt4(const char* name, const int values[4]) const
{
    glUniform4iv(glGetUniformLocation(ID, name), 4, values); 
}

void GL::GLSLProgram::setInt4(const char* name, const int& x, const int& y, const int& z, const int& w) const
{
    glUniform4i(glGetUniformLocation(ID, name), x, y, z, w); 
}

void GL::GLSLProgram::setUInt4(const char* name, const unsigned int values[4]) const
{
    glUniform4uiv(glGetUniformLocation(ID, name), 4, values); 
}

void GL::GLSLProgram::setUInt4(const char* name, const unsigned int& x, const unsigned int& y, const unsigned int& z, const unsigned int& w) const
{
    glUniform4ui(glGetUniformLocation(ID, name), x, y, z, w); 
}

void GL::GLSLProgram::setFloat4(const char* name, const float values[4]) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 4, values); 
}

void GL::GLSLProgram::setFloat4(const char* name, const float& x, const float& y, const float& z, const float& w) const
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
}