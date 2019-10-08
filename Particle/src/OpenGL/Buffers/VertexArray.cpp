#include "PCHeader.h"
#include "VertexArray.h"

GL::VertexArray::VertexArray()
    : ID(0)
{
    GLCheck(glGenVertexArrays(1, &ID));
}

GL::VertexArray::~VertexArray()
{
    GLCheck(glDeleteVertexArrays(1, &ID));
}

void GL::VertexArray::setVertexLayout(VBOLayout layout)
{
    this->bind();

    const auto &elements = layout.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); ++i)
    {
        const auto &element = elements[i];
        GLCheck(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *)offset));
        offset += element.count * VBElement::getSizeOfType(element.type);
        GLCheck(glEnableVertexAttribArray(i));
    }
}

void GL::VertexArray::init()
{
    GLCheck(glBindVertexArray(ID));
}

void GL::VertexArray::bind()
{
    GLCheck(glBindVertexArray(ID));
}

void GL::VertexArray::unbind()
{
    GLCheck(glBindVertexArray(0));
}
