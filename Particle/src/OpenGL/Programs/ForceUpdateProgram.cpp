#include "PCHeader.h"
#include "ForceUpdateProgram.h"

namespace GL
{
GL::ForceUpdateProgram::ForceUpdateProgram()
{
}

GL::ForceUpdateProgram::~ForceUpdateProgram()
{
}

bool GL::ForceUpdateProgram::init(const char *vertexPath, const char *fragmentPath)
{
  GL_LOG_TRACE("Starting update program init.");

  int vertexShader = glCreateShader(GL_VERTEX_SHADER);

  if (!compileShader(vertexPath, vertexShader))
  {
	return false;
  }
  ID = glCreateProgram();
  GLCheck(glAttachShader(ID, vertexShader));

  const GLchar *feedbackVaryings[] = {"outForce" };
  glTransformFeedbackVaryings(ID, 1, feedbackVaryings, GL_INTERLEAVED_ATTRIBS);

  GLCheck(glLinkProgram(ID));

  int success = 0;
  char *infolog;
  GLCheck(glGetProgramiv(ID, GL_LINK_STATUS, &success));
  if (!success)
  {
	glGetProgramInfoLog(ID, 512, NULL, infolog);
	GL_LOG_CRITICAL("{}", infolog);
	return false;
  }
  GLCheck(glDeleteShader(vertexShader));

  GL_LOG_TRACE("UpdateProgram created with id: {}", ID);

  return true;
}
}