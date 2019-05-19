#include "PTProgram.h"

PT::PTProgram::PTProgram(const char* vertexPath, const char* fragmentPath, int args)
    : ID(0)
{
    // Vertex Shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GL::compileShader(vertexPath, vertexShader);

	// Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GL::compileShader(fragmentPath, fragmentShader);

	// Link Shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

    if (args == 1)
    {
        static const char * varyings2[] =
        {
            "world_space_position"
        };
        glTransformFeedbackVaryings(ID, 1, varyings2, GL_INTERLEAVED_ATTRIBS);
    }
    else
    {
        static const char * varyings[] =
        {
            "position_out", "velocity_out"
        };
        glTransformFeedbackVaryings(ID, 2, varyings, GL_INTERLEAVED_ATTRIBS);
    }

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

PT::PTProgram::~PTProgram()
{
    glDeleteProgram(ID);
}

void PT::PTProgram::use()
{
    glUseProgram(ID);
}

void PT::PTProgram::unuse()
{
    glUseProgram(0);
}

// SECTION: Uniform Helper Functions
void PT::PTProgram::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name), value); 
}

void PT::PTProgram::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name), value); 
}

void PT::PTProgram::setInt2(const char* name, const glm::ivec2& values) const
{
    glUniform2iv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}

void PT::PTProgram::setInt2(const char* name, const int& x, const int& y) const
{
    glUniform2i(glGetUniformLocation(ID, name), x, y); 
}

void PT::PTProgram::setFloat2(const char* name, const glm::vec2& values) const
{
    glUniform2fv(glGetUniformLocation(ID, name), 2, glm::value_ptr(values)); 
}
void PT::PTProgram::setFloat2(const char* name, const float& x, const float& y) const
{
    glUniform2f(glGetUniformLocation(ID, name), x, y); 
}

void PT::PTProgram::setInt3(const char* name, const glm::ivec3& values) const
{
    glUniform3iv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void PT::PTProgram::setInt3(const char* name, const int& x, const int& y, const int& z) const
{
    glUniform3i(glGetUniformLocation(ID, name), x, y, z); 
}

void PT::PTProgram::setFloat3(const char* name, const glm::vec3& values) const
{
    glUniform3fv(glGetUniformLocation(ID, name), 3, glm::value_ptr(values)); 
}

void PT::PTProgram::setFloat3(const char* name, const float& x, const float& y, const float& z) const
{
    glUniform3f(glGetUniformLocation(ID, name), x, y, z); 
}

void PT::PTProgram::setInt4(const char* name, const glm::ivec4& values) const
{
    glUniform4iv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void PT::PTProgram::setInt4(const char* name, const int& x, const int& y, const int& z, const int& w) const
{
    glUniform4i(glGetUniformLocation(ID, name), x, y, z, w); 
}

void PT::PTProgram::setFloat4(const char* name, const glm::vec4& values) const
{
    glUniform4fv(glGetUniformLocation(ID, name), 4, glm::value_ptr(values)); 
}

void PT::PTProgram::setFloat4(const char* name, const float& x, const float& y, const float& z, const float& w) const
{
    glUniform4f(glGetUniformLocation(ID, name), x, y, z, w); 
}

void PT::PTProgram::setMat4x4f(const char* name, const glm::mat4& values)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(values));
}