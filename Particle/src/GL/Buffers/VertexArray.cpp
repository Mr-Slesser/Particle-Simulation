#include "VertexArray.h"

GL::VertexArray::VertexArray(/* args */)
    : ID(0)
{
    glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

GL::VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &ID);
}

void GL::VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset);
        offset += element.count * VBElement::getSizeOfType(element.type);
	    glEnableVertexAttribArray(i);
    }
}

void GL::VertexArray::bind() const
{
    glBindVertexArray(ID);
}

void GL::VertexArray::unbind() const
{
    glBindVertexArray(0);
}