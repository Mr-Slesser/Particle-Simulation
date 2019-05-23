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
    Vertex v[1000];
    ZERO_MEM(v);

    va->initBuffers(q);
    // va->initBuffers(v);

    for (int i = 0; i < 1000; i++)
    {
        positions[i] = glm::vec3(
            (((float)(rand() % 100) / 100.0f) * 30) - 15,
            (((float)(rand() % 100) / 100.0f) * 30) - 15,
            (((float)(rand() % 100) / 100.0f) * 10) - 5
        );
    }
    

    return true;
}

void GL::Renderer::clear()
{
    GLCheck(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
	GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::Renderer::draw()
{
    program->use();
    
    viewMatrix();
    projectionMatrix();

    va->use();
    //int count = 0;
    for(unsigned int i = 0; i < 1000; i++)
    {
        //GL_LOG_TRACE("{}, {}, {}", positions[i].x, positions[i].y, positions[i].z);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, positions[i]);
        float angle = 20.0f * (i); 
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
        program->setMat4("model", model);

        GLCheck(glDrawArrays(GL_POINTS, 0, 1));
        //count++;
    }
    
    //GL_LOG_WARN("{}", count);
    // for (unsigned int i = 0; i < 1000; i++)
    // {
    //     glm::vec3 pos = glm::vec3(
    //         (((rand() % 100) / 100) * 30) - 15,
    //         (((rand() % 100) / 100) * 30) - 15,
    //         (((rand() % 100) / 100) * 30) - 15
    //     );
    //     glm::mat4 model = glm::mat4(1.0f);
    //     model = glm::translate(model, pos);
    //     float angle = 20.0f * (i + 1); 
    //     model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //     program->setMat4("model", model);

    //     GLCheck(glDrawArrays(GL_POINTS, 0, 1));
    // }


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