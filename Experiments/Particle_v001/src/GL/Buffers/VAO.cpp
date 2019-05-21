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

void GL::VAO::addBuffer(const GLSLProgram* program, const VBO& vb, const VBOLayout& layout)
{
    bind();
    vb.bind();
    const auto& elements = layout.getElements();
    unsigned int offset = 0;
    for (int i = 0; i < elements.size(); ++i)
    {
        const auto& element = elements[i];
        glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride() + sizeof(glm::mat4), (const void*)offset);
        offset += element.count * VBElement::getSizeOfType(element.type);
	    glEnableVertexAttribArray(i);
    }

    // int pos = glGetAttribLocation(program->getID(), "tForm");
    // for (int i = 0; i < 4; ++i)
    // {
	//     glEnableVertexAttribArray(pos + i);
    //     glVertexAttribPointer(pos + i, 4, GL_FLOAT, GL_FALSE, 
    //         layout.getStride() + sizeof(glm::mat4), 
    //         (void*)((offset + (sizeof(glm::vec4) * i)))
    //         );
    //     glVertexAttribDivisor(pos + i, 1);
    // }
}

void GL::VAO::bind() const
{
    glBindVertexArray(ID);
}

void GL::VAO::unbind() const
{
    glBindVertexArray(0);
}