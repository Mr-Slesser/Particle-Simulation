#include "IndexBuffer.h"

GL::IndexBuffer::IndexBuffer(const unsigned int* _data, unsigned int _count, int _draw)
    : ID(0), count(_count)
{
    glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), _data, _draw);
}

GL::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void GL::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GL::IndexBuffer::unbind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}