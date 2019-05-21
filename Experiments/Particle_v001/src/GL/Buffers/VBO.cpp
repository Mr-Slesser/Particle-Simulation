#include "VBO.h"

GL::VBO::VBO(const void* _data, unsigned int _size, int _draw)
    : ID(0)
{
    glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, _size, _data, _draw);
}

GL::VBO::~VBO()
{
    glDeleteBuffers(1, &ID);
}

void GL::VBO::bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void GL::VBO::unbind() const 
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}