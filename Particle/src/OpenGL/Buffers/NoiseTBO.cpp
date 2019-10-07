#include "PCHeader.h"
#include "NoiseTBO.h"

namespace GL
{
NoiseTBO::NoiseTBO(GLenum _textureUnit, std::vector<glm::vec3> &_force)
    : textureUnit(_textureUnit)
{
    PROFILE("NoiseTBO::NoiseTBO");

    GLCheck(glGenBuffers(1, &bufferID));
    GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
    GLCheck(glBufferData(GL_TEXTURE_BUFFER, _force.size() * sizeof(glm::vec3), _force.data(), GL_DYNAMIC_DRAW));
    GLCheck(glGenTextures(1, &bufferTextureID));
    GLCheck(glBindTexture(GL_TEXTURE_BUFFER, bufferTextureID));
    GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, bufferID));
}

NoiseTBO::~NoiseTBO()
{
    glDeleteBuffers(1, &bufferID);
}

void NoiseTBO::bindTexture()
{
    PROFILE("NoiseTBO::bind");

    GLCheck(glActiveTexture(textureUnit));
    GLCheck(glBindTexture(GL_TEXTURE_BUFFER, bufferTextureID));
    GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, bufferID));
}

glm::vec3 *NoiseTBO::getPointer()
{
    PROFILE("NoiseTBO::getPointer");

    GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
    return (glm::vec3 *)glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
}

void NoiseTBO::releasePointer()
{
    PROFILE("NoiseTBO::releasePointer");

    GLCheck(glUnmapBuffer(GL_TEXTURE_BUFFER));
}

void NoiseTBO::loadData(glm::vec3 *pointer, int size)
{
    PROFILE("NoiseTBO::loadData");

    GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, bufferID));
    auto bufferPointer = getPointer();
    memcpy(bufferPointer, pointer, size);
    releasePointer();
}

} // namespace GL