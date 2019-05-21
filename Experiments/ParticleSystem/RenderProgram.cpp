#include "RenderProgram.h"

PT::RenderProgram::RenderProgram(const char* vertexPath, const char* fragmentPath, const char* geomPath)
    : ID(0)
{
    // Vertex Shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GL::compileShader(vertexPath, vertexShader);

	// Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GL::compileShader(fragmentPath, fragmentShader);

    // Geometry Shader
	int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    GL::compileShader(geomPath, geometryShader);

	// Link Shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);
	glAttachShader(ID, geometryShader);

	glLinkProgram(ID);

    // Check for linking errors
    int success = 1;
    char infolog[1024] = { 0 };
	glGetProgramiv(ID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(ID, sizeof(infolog), NULL, infolog);
        FATAL(Error::TYPE::PROGRAM_SHADER_LINK, infolog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteShader(geometryShader);
}

PT::RenderProgram::~RenderProgram()
{
    glDeleteProgram(ID);
}

void PT::RenderProgram::use()
{
    glUseProgram(ID);
}

void PT::RenderProgram::unuse()
{
    glUseProgram(0);
}

// SECTION: Uniform Helper Functions
void PT::RenderProgram::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value); 
}

void PT::RenderProgram::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value); 
}

void PT::RenderProgram::setInt2(const char* name, const glm::ivec2& values) const
{
    glUniform2iv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}

void PT::RenderProgram::setInt2(const char* name, const int& x, const int& y) const
{
    glUniform2i(glGetUniformLocation(ID, name), x, y); 
}

void PT::RenderProgram::setFloat2(const char* name, const glm::vec2& values) const
{
    glUniform2fv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}
void PT::RenderProgram::setFloat2(const char* name, const float& x, const float& y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y); 
}

void PT::RenderProgram::setInt3(const char* name, const glm::ivec3& values) const
{
    glUniform3iv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void PT::RenderProgram::setInt3(const char* name, const int& x, const int& y, const int& z) const
{
    glUniform3i(glGetUniformLocation(ID, name), x, y, z); 
}

void PT::RenderProgram::setFloat3(const char* name, const glm::vec3& values) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void PT::RenderProgram::setFloat3(const char* name, const float& x, const float& y, const float& z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
}

void PT::RenderProgram::setInt4(const char* name, const glm::ivec4& values) const
{
    glUniform4iv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void PT::RenderProgram::setInt4(const char* name, const int& x, const int& y, const int& z, const int& w) const
{
    glUniform4i(glGetUniformLocation(ID, name), x, y, z, w); 
}

void PT::RenderProgram::setFloat4(const char* name, const glm::vec4& values) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void PT::RenderProgram::setFloat4(const char* name, const float& x, const float& y, const float& z, const float& w) const
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
}

void PT::RenderProgram::setMat4x4f(const char* name, const glm::mat4& values)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(values));
}