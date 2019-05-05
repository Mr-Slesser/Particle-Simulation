#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Helpers.hpp"
#include "../Utility/Error.hpp"

int program_init() {
    // Vertex Shader
	int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GL::compileShader("./Particle/src/Resources/Shaders/bagsic.vertex", vertexShader);

	// Fragment Shader
	int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    GL::compileShader("./Particle/src/Resources/Shaders/basic.fragment", fragmentShader);

	// Link Shaders
	int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

    //Error::fatal(Error::TYPE::PROGRAM_SHADER_LOAD, "Could not load");

    // check for linking errors
    int success = 0;
    char* infolog;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
        // TODO: Error this.
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infolog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

    return shaderProgram;
}
