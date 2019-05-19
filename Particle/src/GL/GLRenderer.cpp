#include "GLRenderer.h"

GL::GLRenderer::GLRenderer()
{

}

GL::GLRenderer::~GLRenderer()
{

}

// void GL::GLRenderer::init(unsigned int indices[6], Vertex v[4], int vsize) 
void GL::GLRenderer::init(Vertex v[4], int vsize) 
{
    program = new GLSLProgram();
    vao = new VAO();
    vbo = new VBO(v, vsize, GL_STATIC_DRAW);

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3);
    vbl.push<float>(4);

    vao->addBuffer(program, *vbo, vbl);
    ib = new QuadIndexBuffer(GLRENDERER_INDICES_SIZE);

    view = glm::mat4(1.0f);
    projection = glm::mat4(1.0f);
}

void GL::GLRenderer::viewMatrix(float& dt, Camera* cam)
{
    // TODO: Can only call if this progran is bound.
    // TODO: Camera to update this on change.
    view = cam->getLookAt();
    int viewLoc = glGetUniformLocation(program->getID(), "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void GL::GLRenderer::projectionMatrix(float& dt, Camera* cam)
{
    // TODO: Can only call if this progran is bound.
    // TODO: Camera to update this on change.
    projection = cam->getProjection();
    int projectionLoc = glGetUniformLocation(program->getID(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void GL::GLRenderer::clear() const
{
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GL::GLRenderer::draw(float& dt, Camera* cam)
{
    program->use();
    program->setFloat("time", dt);

    viewMatrix(dt, cam);
    projectionMatrix(dt, cam);

    vao->bind();

    GLuint tbo;
    glGenBuffers(1, &tbo);
    glBindBuffer(GL_ARRAY_BUFFER, tbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(PT::Quad), nullptr, GL_STATIC_READ);

    ib->bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
}