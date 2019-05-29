#include "VertexArray.h"

GL::VertexArray::VertexArray()
    : VAO(0), VBO(0), EBO(0)
{
    GLCheck(glGenVertexArrays(1, &VAO));
    GLCheck(glGenBuffers(1, &VBO));
    GLCheck(glGenBuffers(1, &EBO));
}

GL::VertexArray::~VertexArray()
{
    GLCheck(glDeleteVertexArrays(1, &VAO));
    GLCheck(glDeleteBuffers(1, &VBO));
    GLCheck(glDeleteBuffers(1, &EBO));
}

void GL::VertexArray::initBuffers(Cube& q)
{
    this->use();
    
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(q.vertices), q.vertices, GL_STATIC_DRAW));

    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
    GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(q.indices), q.indices, GL_STATIC_DRAW));

    GLCheck(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0));
    GLCheck(glEnableVertexAttribArray(0));
    GLCheck(glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float))));
    GLCheck(glEnableVertexAttribArray(1));
    GLCheck(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(7 * sizeof(float))));
    GLCheck(glEnableVertexAttribArray(2));
}

void GL::VertexArray::use()
{
    GLCheck(glBindVertexArray(VAO));
    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, VBO));
    GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO));
}