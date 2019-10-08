#include "PCHeader.h"
#include "DebugProgram.h"

GL::DebugProgram::DebugProgram()
{
}

bool GL::DebugProgram::Init(const char *vertexPath, const char *fragmentPath)
{
  int vertexShader = glCreateShader(GL_VERTEX_SHADER);

  if (!CompileShader(vertexPath, vertexShader))
  {
	return false;
  }

  int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  if (!CompileShader(fragmentPath, fragmentShader))
  {
	return false;
  }

  ID = glCreateProgram();
  GLCheck(glAttachShader(ID, vertexShader));
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
  GLCheck(glDeleteShader(fragmentShader));

  GL_LOG_TRACE("Program created with id: {}", ID);

  return true;
}