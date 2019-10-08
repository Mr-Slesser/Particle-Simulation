#include "PCHeader.h"
#include "DebugProgram.h"

GL::DebugProgram::DebugProgram()
{
}

bool GL::DebugProgram::init(const char *vertexPath, const char *fragmentPath)
{
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);

  if (!compileShader(vertexPath, vertexShader))
  {
	return false;
  }

//  int geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
//  if (!compileShader(PATH("Shaders/Debug/debug.geometry.glsl"), geometryShader))
//  {
//	return false;
//  }

  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (!compileShader(fragmentPath, fragmentShader))
  {
	return false;
  }

  ID = glCreateProgram();
  GLCheck(glAttachShader(ID, vertexShader));
//  GLCheck(glAttachShader(ID, geometryShader));
  GLCheck(glAttachShader(ID, fragmentShader));
  GLCheck(glLinkProgram(ID));

  int success = 0;
  char *infolog;
  GLCheck(glGetProgramiv(ID, GL_LINK_STATUS, &success));
  if (!success)
  {
	glGetProgramInfoLog(ID, 512, NULL, infolog);
	std::cout << infolog << std::endl;
	GL_LOG_CRITICAL("{}", infolog);
	return false;
  }

  GLCheck(glDeleteShader(vertexShader));
//  GLCheck(glDeleteShader(geometryShader));
  GLCheck(glDeleteShader(fragmentShader));

  GL_LOG_TRACE("Program created with id: {}", ID);

  return true;
}