#include "Renderer.h"
#include "GLLog.h"

GL::Renderer::Renderer()
    : vd(VertexData(MAX_PARTICLES))
{
    pointer = new VBPointer();
    pointer->start = pointer->it = nullptr;
    pointer->size = 0;
}

GL::Renderer::~Renderer()
{
    delete program;
    delete va;
    delete pointer;

    for (auto p : particles)
    {
        delete p;
    }

    particles.clear();
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
    va->initBuffers(sizeof(Vertex) * MAX_PARTICLES);

    // pointer->start = pointer->it = va->getBuffer()->getPointer();
    // for (int i = 0; i < (50 * 50); i++)
    // {
    //     pointer->it->position = glm::vec3(
    //             (((float)(rand() % 100) / 100.0f) * (rand() % 5000)) - 2500,
    //             (((float)(rand() % 100) / 100.0f) * (rand() % 5000)) - 2500,
    //             (((float)(rand() % 100) / 100.0f) * 1000));
    //     pointer->it->colour = Colour::PINK;

    //     pointer->it++;
    //     pointer->size++;
    // }
    // va->getBuffer()->releasePointer();

    pointer->start = pointer->it = va->getBuffer()->getPointer();
    for (int i = 0; i < total; i++)
    {
        float lat = PT::map<float>(i, 0, total, -HALF_PI, HALF_PI);
        for (int j = 0; j < total; j++)
        {
            float lon = PT::map<float>(j, 0, total, -PI, PI);

            float x = 100 * sin(lon) * cos(lat);
            float y = 100 * sin(lon) * sin(lat);
            float z = 100 * cos(lon);
            
            pointer->it->position = glm::vec3(x, y, z);
            pointer->it->colour = Colour::PINK;
            pointer->it++;
            pointer->size++;
        }
    }
    va->getBuffer()->releasePointer();

    return true;
}

void GL::Renderer::clear()
{
    GLCheck(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
	GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::Renderer::update()
{
    // pointer->start = pointer->it = va->getBuffer()->getPointer();
    // for (int i = 0; i < 1000; i++)
    // {
    //     pointer->it->position = pointer->it->position + glm::vec3(0.2f, 0.3f, 0.1f);

    //     pointer->it++;
    // }
    // va->getBuffer()->releasePointer();    

    // pointer->start = pointer->it = va->getBuffer()->getPointer();
    // for (int i = 0; i < (total * total); i++)
    // {
    //     float lat = PT::map<float>(i, 0, total, -HALF_PI, HALF_PI);
    //     for (int j = 0; j < total; j++)
    //     {
    //         pointer->it->position = pointer->it->position + glm::vec3(0.1f, 0.1f, 0.1f);
    //         pointer->it++;
    //     }
    // }
    // va->getBuffer()->releasePointer();
}

void GL::Renderer::draw()
{
    program->use();
    
    viewMatrix();
    projectionMatrix();

    va->use();

    glm::mat4 model = glm::mat4(1.0f);  
    model = glm::rotate(model, (float)glfwGetTime() * (float)PI, glm::vec3(1.0f, 0.3f, 0.5f));
    program->setMat4("model", model);  
    GLCheck(glDrawArrays(GL_POINTS, 0, pointer->size - 1));

    // for(unsigned int i = 0; i < pointer->size; i++)
    // {
    //     glm::mat4 model = glm::mat4(1.0f);
    //     float angle = 0.01f * (i); 
    //     model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
    //     program->setMat4("model", model);
    //     GLCheck(glDrawArrays(GL_POINTS, i, 1));
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
    program->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
}

void GL::Renderer::projectionMatrix()
{
    program->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());
}