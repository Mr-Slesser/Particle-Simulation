#include "Renderer.h"
#include "GLLog.h"

GL::Renderer::Renderer()
    : vd(VertexData(MAX_PARTICLES))
{
    pointer = new VBPointer();
    pointer->start = pointer->it = nullptr;
    pointer->size = 0;
    PT::GC::get()->init();
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
        GL_LOG_CRITICAL("GL::Renderer::init() -> Render Program failed to init");
        return false;
    }

    update_program = new UpdateProgram();
    if (!update_program->ainit())
    {
        GL_LOG_CRITICAL("GL::Renderer::init() -> Update Program failed to init");
        return false;
    }

    for (int i = 0; i < total; i++)
    {
        float lat = PT::map<float>(i, 0, total, -HALF_PI, HALF_PI);
        for (int j = 0; j < total; j++)
        {
            float lon = PT::map<float>(j, 0, total, -PI, PI);

            float x = 100 * sin(lon) * cos(lat);
            float y = 100 * sin(lon) * sin(lat);
            float z = 100 * cos(lon);
            Vertex v;        
            v.position = glm::vec3(x, y, z);
            v.colour = Colour::PINK;
            vd.add(v);
        }
    }

    vaU = new VertexArray();
    vaU->init();

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3, 0);
    vbl.push<float>(4, 1);

    vb1 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb1->init(sizeof(Vertex) * MAX_PARTICLES);

    pointer->start = pointer->it = vb1->getPointer();
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
    vb1->releasePointer();
    PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);

    vb2 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb2->init(sizeof(Vertex) * MAX_PARTICLES);

    vb1->bind();

    vaU->setVertexLayout(vbl);

    vaR = new VertexArray();
    vaR->init();
    vaR->setVertexLayout(vbl);

    vb1->bind();
 
    vaR->setVertexLayout(vbl);

    Print_All(program->getID());
    Print_All(update_program->getID());

    return true;
}

void GL::Renderer::clear()
{
    GLCheck(glClearColor(0.2f, 0.2f, 0.2f, 1.0f));
	GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::Renderer::update()
{
    static float dt = 0.0f;
    update_program->use();
    vaU->use(1);
    update_program->setFloat("dt", dt);
    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vb2->getID());
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, pointer->size - 1);
    glEndTransformFeedback();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();
    
    glDisable(GL_RASTERIZER_DISCARD);

    std::swap(vb1, vb2);
    glBindVertexArray(0);
    dt += 0.001;
}

void GL::Renderer::draw()
{
    this->update();

    program->use();
    
    viewMatrix();
    projectionMatrix();

    vaR->use(1);

    glm::mat4 model = glm::mat4(1.0f);  
    //model = glm::rotate(model, (float)glfwGetTime() * (float)PI, glm::vec3(1.0f, 0.3f, 0.5f));
    program->setMat4("model", model);

    GLCheck(glDrawArrays(GL_POINTS, 0, pointer->size - 1));
}

void GL::Renderer::modelMatrix()
{
    model = glm::mat4(1.0f);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
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

void GL::Renderer::addParticle(int num)
{
    vb1->bind();
    pointer->it = vb1->getPointer() + pointer->size - 1;
    for (int i = 0; i < num; ++i)
    {
        if (pointer->size >= PT::GC::get()->getInt("MAX_PARTICLES")) break;

        pointer->it->position = glm::vec3(random() % 8000 - 4000, random() % 8000 - 4000, random() % 5000 - 2500);
        pointer->it->colour = Colour::BLUE;
        pointer->it++;
        pointer->size++;


    }
    vb1->releasePointer();
    PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);
}