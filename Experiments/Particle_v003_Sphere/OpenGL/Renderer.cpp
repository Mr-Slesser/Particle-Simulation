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

    // SECTION: TFO Setup

    update_program = new UpdateProgram();
    if (!update_program->init())
    {
        GL_LOG_CRITICAL("Update Program failed to init");
        return false;
    }

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);

    inputAttrib = glGetAttribLocation(update_program->getID(), "inValue");
    glEnableVertexAttribArray(inputAttrib);
    glVertexAttribPointer(inputAttrib, 1, GL_FLOAT, GL_FALSE, 0, 0);

    glGenBuffers(1, &tbo);
    glBindBuffer(GL_TRANSFORM_FEEDBACK_BUFFER, tbo);
    glBufferData(GL_TRANSFORM_FEEDBACK_BUFFER, sizeof(data), nullptr, GL_STATIC_READ);

    // SECTION: End TFO Setup


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
    update_program->use();
    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, tbo);
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, 5);
    glEndTransformFeedback();
    glFlush();
    GLfloat feedback[5];
    glGetBufferSubData(GL_TRANSFORM_FEEDBACK_BUFFER, 0, sizeof(feedback), feedback);
    CORE_LOG_INFO("{} {} {} {} {}", feedback[0], feedback[1], feedback[2], feedback[3], feedback[4]);
    glDisable(GL_RASTERIZER_DISCARD);

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