#include "UpdateProgram.h"

PT::UpdateProgram::UpdateProgram(const char* vertexPath, const char* fragmentPath, const char* geomPath)
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

    const GLchar* Varyings[4];    
    Varyings[0] = "Type1";
    Varyings[1] = "Position1";
    Varyings[2] = "Velocity1";    
    Varyings[3] = "Age1";
    
    glTransformFeedbackVaryings(ID, 4, Varyings, GL_INTERLEAVED_ATTRIBS);

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

PT::UpdateProgram::~UpdateProgram()
{
    glDeleteProgram(ID);
}

void PT::UpdateProgram::use()
{
    glUseProgram(ID);
}

void PT::UpdateProgram::unuse()
{
    glUseProgram(0);
}

// SECTION: Uniform Helper Functions
void PT::UpdateProgram::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value); 
}

void PT::UpdateProgram::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value); 
}

void PT::UpdateProgram::setInt2(const char* name, const glm::ivec2& values) const
{
    glUniform2iv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}

void PT::UpdateProgram::setInt2(const char* name, const int& x, const int& y) const
{
    glUniform2i(glGetUniformLocation(ID, name), x, y); 
}

void PT::UpdateProgram::setFloat2(const char* name, const glm::vec2& values) const
{
    glUniform2fv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}
void PT::UpdateProgram::setFloat2(const char* name, const float& x, const float& y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y); 
}

void PT::UpdateProgram::setInt3(const char* name, const glm::ivec3& values) const
{
    glUniform3iv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void PT::UpdateProgram::setInt3(const char* name, const int& x, const int& y, const int& z) const
{
    glUniform3i(glGetUniformLocation(ID, name), x, y, z); 
}

void PT::UpdateProgram::setFloat3(const char* name, const glm::vec3& values) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void PT::UpdateProgram::setFloat3(const char* name, const float& x, const float& y, const float& z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
}

void PT::UpdateProgram::setInt4(const char* name, const glm::ivec4& values) const
{
    glUniform4iv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void PT::UpdateProgram::setInt4(const char* name, const int& x, const int& y, const int& z, const int& w) const
{
    glUniform4i(glGetUniformLocation(ID, name), x, y, z, w); 
}

void PT::UpdateProgram::setFloat4(const char* name, const glm::vec4& values) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void PT::UpdateProgram::setFloat4(const char* name, const float& x, const float& y, const float& z, const float& w) const
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
}

void PT::UpdateProgram::setMat4x4f(const char* name, const glm::mat4& values)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(values));
}