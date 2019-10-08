#include "PCHeader.h"
#include "TextureBuffer.h"

TextureBuffer::TextureBuffer(GLenum _textureUnit)
	: textureUnit(_textureUnit)
{
  PROFILE("TextureBuffer::TextureBuffer");

//    GLCheck(glGenBuffers(1, &bufferID));
//    GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
//    GLCheck(glBufferData(GL_TEXTURE_BUFFER, force->size(), force->getDataPointer(), GL_DYNAMIC_DRAW));
//    GLCheck(glGenTextures(1, &bufferTextureID));
//    GLCheck(glBindTexture(GL_TEXTURE_BUFFER, bufferTextureID));
//    GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, bufferID));
}

TextureBuffer::~TextureBuffer()
{
  glDeleteBuffers(1, &bufferID);
}

void TextureBuffer::bindTexture()
{
  PROFILE("TextureBuffer::bind");

  GLCheck(glActiveTexture(textureUnit));
  GLCheck(glBindTexture(GL_TEXTURE_BUFFER, bufferTextureID));
  GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, bufferID));
}

glm::vec3 *TextureBuffer::getPointer()
{
  PROFILE("TextureBuffer::getPointer");

  GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
  return (glm::vec3 *) glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
}

void TextureBuffer::releasePointer()
{
  PROFILE("TextureBuffer::releasePointer");

  GLCheck(glUnmapBuffer(GL_TEXTURE_BUFFER));
}

void TextureBuffer::loadData()
{
  PROFILE("TextureBuffer::loadData");

//  GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
//  auto bufferPointer = getPointer();
//  memcpy(bufferPointer, force->getDataPointer(), force->size());
//  releasePointer();
}
