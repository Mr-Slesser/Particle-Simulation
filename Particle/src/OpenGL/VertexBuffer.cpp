#include "PCHeader.h"
#include "VertexBuffer.h"

namespace GL
{
VertexBuffer::VertexBuffer(GLenum _usage)
    : ID(0), size(0), usage(_usage)
{
    GLCheck(glGenBuffers(1, &ID));
}

VertexBuffer::~VertexBuffer()
{
    GLCheck(glDeleteBuffers(1, &ID));
}

void VertexBuffer::init(const unsigned long &_size)
{
    GL_LOG_TRACE("VertexBuffer::init (null): Size: {}", _size);
    size = _size;
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
    GLCheck(glBufferData(GL_ARRAY_BUFFER, size, NULL, usage));
}

void VertexBuffer::init(const unsigned long &_size, VertexData &vd)
{
    GL_LOG_TRACE("VertexBuffer::init (data): Size: {}", _size);
    size = _size;
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
    GLCheck(glBufferData(GL_ARRAY_BUFFER, size, vd.get().data(), usage));
}

void VertexBuffer::bind()
{
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
}

PT::ParticleData *VertexBuffer::getPointer()
{
    return (PT::ParticleData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void VertexBuffer::releasePointer()
{
    GLCheck(glUnmapBuffer(GL_ARRAY_BUFFER));
}

} // namespace GL
