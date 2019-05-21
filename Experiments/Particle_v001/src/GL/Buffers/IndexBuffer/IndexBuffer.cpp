#include "IndexBuffer.h"

GL::IndexBuffer::IndexBuffer(int size)
    : ID(0), count(size)
{
}

GL::IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &ID);
}

void GL::IndexBuffer::init(unsigned int* indices)
{
    glGenBuffers(1, &ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

void GL::IndexBuffer::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GL::IndexBuffer::unbind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}