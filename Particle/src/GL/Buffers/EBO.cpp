#include "EBO.h"

GL::EBO::EBO(const unsigned int* _data, unsigned int _count, int _draw)
    : ID(0), count(_count)
{
    glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), _data, _draw);
}

GL::EBO::~EBO()
{
    glDeleteBuffers(1, &ID);
}

void GL::EBO::bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void GL::EBO::unbind() const 
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}