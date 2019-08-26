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

void GL::VertexArray::setVertexLayout(VBOLayout &layout)
{
    //this->use();

    const auto &elements = layout.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); ++i)
    {
        const auto &element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void *)offset);
        offset += element.count * VBElement::getSizeOfType(element.type);
        glEnableVertexAttribArray(i);
    }
}

void GL::VertexArray::init()
{
    GLCheck(glBindVertexArray(ID));

    // GL::VBOLayout vbl = VBOLayout();
    // vbl.push<float>(3, 0);
    // vbl.push<float>(4, 1);
    // this->setVertexLayout(vbl);
}

void GL::VertexArray::initBuffers(const unsigned long &size)
{
    GLCheck(glBindVertexArray(ID));
    buffers.push_back(new VertexBuffer(GL_DYNAMIC_DRAW));
    buffers.front()->init(size);

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3, 0);
    vbl.push<float>(4, 1);
    this->setVertexLayout(vbl);
}

void GL::VertexArray::use()
{
    GLCheck(glBindVertexArray(ID));
    this->bindVBO();
}

void GL::VertexArray::use(int a)
{
    GLCheck(glBindVertexArray(ID));
}

void GL::VertexArray::use(VertexBuffer *vb)
{
    GLCheck(glBindVertexArray(ID));
    vb->bind();
}

void GL::VertexArray::bindVBO()
{
    buffers.front()->bind();
}