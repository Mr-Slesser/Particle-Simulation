#include "Renderer.h"
#include "GLLog.h"

GL::Renderer::Renderer()
{
}

GL::Renderer::~Renderer()
{
}

bool GL::Renderer::init()
{
    program = new Program();
    if (!program->init())
    {
        GL_LOG_CRITICAL("Program failed to init");
        return false;
    }

    Print_All(program->getID());

    va = new VertexArray();
    va->initBuffers(q);
    t = new Texture(TEXTURE_LOC, GL_TEXTURE_2D);
    return true;
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
    program->setMat4("model", glm::mat4(1.0f));
}

void GL::Renderer::viewMatrix()
{
    // TODO: Camera to update this on change.
    program->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
}

void GL::Renderer::projectionMatrix()
{
    // TODO: Camera to update this on change.
    program->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());
}

void GL::Renderer::changeShaders(int type)
{
    switch(type)
    {
        case 1:
            program->init();
            break;
        case 2: 
            program->init(VS_TEST, FS_TEST);
            break;
    }
}
