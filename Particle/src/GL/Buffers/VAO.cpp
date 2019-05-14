#include "VAO.h"

GL::VAO::VAO(/* args */)
    : ID(0)
{
    glGenVertexArrays(1, &ID);
	glBindVertexArray(ID);
}

GL::VAO::~VAO()
{
    glDeleteVertexArrays(1, &ID);
}

void GL::VAO::addBuffer(const VBO& vb, const VBOLayout& layout)
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

void GL::VAO::bind() const
{
    glBindVertexArray(ID);
}

void GL::VAO::unbind() const
{
    glBindVertexArray(0);
}