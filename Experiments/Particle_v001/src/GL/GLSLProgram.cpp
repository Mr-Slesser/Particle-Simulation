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

GL::GLSLProgram::~GLSLProgram()
{
    GLCheck(glDeleteProgram(ID));
}

void GL::GLSLProgram::use()
{
    GLCheck(glUseProgram(ID));
}

void GL::GLSLProgram::unuse()
{
    GLCheck(glUseProgram(0));
}

// SECTION: Uniform Helper Functions
void GL::GLSLProgram::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value); 
}

void GL::GLSLProgram::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value); 
}

void GL::GLSLProgram::setInt2(const char* name, const glm::ivec2& values) const
{
    glUniform2iv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}

void GL::GLSLProgram::setInt2(const char* name, const int& x, const int& y) const
{
    glUniform2i(glGetUniformLocation(ID, name), x, y); 
}

void GL::GLSLProgram::setFloat2(const char* name, const glm::vec2& values) const
{
    glUniform2fv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}
void GL::GLSLProgram::setFloat2(const char* name, const float& x, const float& y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y); 
}

void GL::GLSLProgram::setInt3(const char* name, const glm::ivec3& values) const
{
    glUniform3iv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void GL::GLSLProgram::setInt3(const char* name, const int& x, const int& y, const int& z) const
{
    glUniform3i(glGetUniformLocation(ID, name), x, y, z); 
}

void GL::GLSLProgram::setFloat3(const char* name, const glm::vec3& values) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void GL::GLSLProgram::setFloat3(const char* name, const float& x, const float& y, const float& z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
}

void GL::GLSLProgram::setInt4(const char* name, const glm::ivec4& values) const
{
    glUniform4iv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void GL::GLSLProgram::setInt4(const char* name, const int& x, const int& y, const int& z, const int& w) const
{
    glUniform4i(glGetUniformLocation(ID, name), x, y, z, w); 
}

void GL::GLSLProgram::setFloat4(const char* name, const glm::vec4& values) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void GL::GLSLProgram::setFloat4(const char* name, const float& x, const float& y, const float& z, const float& w) const
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
}

void GL::GLSLProgram::setMat4x4f(const char* name, const glm::mat4& values)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(values));
}