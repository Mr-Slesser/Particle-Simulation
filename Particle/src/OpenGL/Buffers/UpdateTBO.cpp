#include "PCHeader.h"
#include "UpdateTBO.h"

namespace GL
{
UpdateTBO::UpdateTBO(GLenum _textureUnit, std::vector<glm::vec3> &_force)
	: textureUnit(_textureUnit)
{
  PROFILE("UpdateTBO::UpdateTBO");

  GLCheck(glGenBuffers(1, &bufferID));
  GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
  GLCheck(glBufferData(GL_TEXTURE_BUFFER, _force.size() * sizeof(glm::vec3), _force.data(), GL_DYNAMIC_DRAW));
  GLCheck(glGenTextures(1, &bufferTextureID));
  GLCheck(glBindTexture(GL_TEXTURE_BUFFER, bufferTextureID));
  GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, bufferID));
}

UpdateTBO::~UpdateTBO()
{
  glDeleteBuffers(1, &bufferID);
}

void UpdateTBO::bindTexture()
{
  PROFILE("UpdateTBO::bind");

  GLCheck(glActiveTexture(textureUnit));
  GLCheck(glBindTexture(GL_TEXTURE_BUFFER, bufferTextureID));
  GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, bufferID));
}

glm::vec3 *UpdateTBO::getPointer()
{
  PROFILE("UpdateTBO::getPointer");

  GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
  return (glm::vec3 *) glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
}

void UpdateTBO::releasePointer()
{
  PROFILE("UpdateTBO::releasePointer");

  GLCheck(glUnmapBuffer(GL_TEXTURE_BUFFER));
}

void UpdateTBO::loadData(glm::vec3 *pointer, int size)
{
  PROFILE("UpdateTBO::loadData");

  GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
  auto bufferPointer = getPointer();
  memcpy(bufferPointer, pointer, size);
  releasePointer();
}

}