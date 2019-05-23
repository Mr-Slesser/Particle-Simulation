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
    if (!program->init(VS_POINT, FS_POINT))
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
    
    //modelMatrix();
    viewMatrix();
    projectionMatrix();

    va->use();

    glPointSize(100.0f);

    for(unsigned int i = 0; i < 10; i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);
        float angle = 20.0f * (i + 1); 
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        program->setMat4("model", model);

        GLCheck(glDrawArrays(GL_POINTS, 0, 36));
    }


}

void GL::Renderer::modelMatrix()
{
    model = glm::mat4(1.0f);
    model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    program->setMat4("model", model);
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
