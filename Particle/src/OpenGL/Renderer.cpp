#include "Renderer.h"
#include "GLLog.h"

GL::Renderer::Renderer()
{
}

GL::Renderer::~Renderer()
{
}

void GL::Renderer::init()
{
    program = new Program();
    print_all(program->getID());

    va = new VertexArray();
    va->initBuffers(q);
    t = new Texture(TEXTURE_LOC, GL_TEXTURE_2D);
}

void GL::Renderer::clear()
{
    GLCheck(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
	GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::Renderer::draw()
{
    t->bind();
    program->use();
    
    modelMatrix();
    viewMatrix();
    projectionMatrix();

    va->use();
    GLCheck(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0));
}

void GL::Renderer::modelMatrix()
{
    model = glm::mat4(1.0f);
    int modelLoc = glGetUniformLocation(program->getID(), "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
}

void GL::Renderer::viewMatrix()
{
    // TODO: Camera to update this on change.
    view = PT::CameraManager::get()->getCamera()->getLookAt();
    int viewLoc = glGetUniformLocation(program->getID(), "view");
    GLCheck(glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view)));
}

void GL::Renderer::projectionMatrix()
{
    // TODO: Camera to update this on change.
    projection = PT::CameraManager::get()->getCamera()->getProjection();
    int projectionLoc = glGetUniformLocation(program->getID(), "projection");
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));
}

void GL::Renderer::changeShaders(int type)
{
    switch(type)
    {
        case 1:
            program = new Program();
            break;
        case 2: 
            program = new Program(VS_TEST, FS_TEST);
            break;
    }
}
