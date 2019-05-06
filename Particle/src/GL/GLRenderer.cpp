#include "GLRenderer.h"

GL::GLRenderer::GLRenderer()
{

}

GL::GLRenderer::~GLRenderer()
{

}

void GL::GLRenderer::clear() const
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GL::GLRenderer::draw(VertexArray* va, IndexBuffer* ib, GLSLProgram* program) const
{
    program->use();
    va->bind();
    ib->bind();
    glDrawElements(GL_TRIANGLES, ib->getCount(), GL_UNSIGNED_INT, nullptr);
}