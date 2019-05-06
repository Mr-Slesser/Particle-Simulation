#include "GLSLProgram.h"

GL::GLSLProgram::GLSLProgram(const char* vertexPath, const char* fragmentPath)
    : _id(0)
{
    // Vertex Shader
    int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    compileShader(vertexPath, vertexShader);

	// Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    compileShader(fragmentPath, fragmentShader);

	// Link Shaders
	_id = glCreateProgram();
	glAttachShader(_id, vertexShader);
	glAttachShader(_id, fragmentShader);
	glLinkProgram(_id);

    // Check for linking errors
    int success = 0;
    char* infolog;
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success) {
        _id = 0;
		glGetProgramInfoLog(_id, 512, NULL, infolog);
        FATAL(Error::TYPE::PROGRAM_SHADER_LINK, infolog);
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
}

GL::GLSLProgram::~GLSLProgram()
{
    glDeleteProgram(_id);
}

void GL::GLSLProgram::use()
{
    glUseProgram(_id);
}

// SECTION: Uniform Helper Functions
void GL::GLSLProgram::setInt(const char* name, int value) const
{
    glUniform1i(glGetUniformLocation(_id, name), value); 
}

void GL::GLSLProgram::setUInt(const char* name, unsigned int value) const
{
    glUniform1ui(glGetUniformLocation(_id, name), value); 
}

void GL::GLSLProgram::setBool(const char* name, bool value) const
{
    glUniform1i(glGetUniformLocation(_id, name), static_cast<int>(value)); 
}

void GL::GLSLProgram::setFloat(const char* name, float value) const
{
    glUniform1f(glGetUniformLocation(_id, name), value); 
}