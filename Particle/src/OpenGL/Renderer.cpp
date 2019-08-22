#include "Renderer.h"
#include "GLLog.h"

GL::Renderer::Renderer()
{
    PROFILE_FUNCTION;
    PT::GC::get()->init();

    vd = VertexData(PT::GC::get()->getInt("MAX_PARTICLES"));
    pointer = new VBPointer();
    pointer->start = pointer->it = nullptr;
    pointer->size = 0;
}

GL::Renderer::~Renderer()
{
    PROFILE_FUNCTION;

    delete programs;
    delete va;
    delete pointer;

#if RENDERER_FORWARD
    delete vb1;
    delete vb2;
    delete vaR;
    delete vaU;
#else
    VertexBuffer *vb;
#endif

    for (auto p : particles)
    {
        delete p;
    }

    particles.clear();
}

bool GL::Renderer::init()
{
    PROFILE_FUNCTION;

    programs = new ProgramManager();
    if (!programs->init())
    {
        GL_LOG_CRITICAL("GL::Renderer::init() -> Program Manager failed to init");
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

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3, 0);
    vbl.push<float>(4, 1);

#if RENDERER_FORWARD
    vaU = new VertexArray();
    vaU->init();

    vb1 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb1->init(sizeof(Vertex) * PT::GC::get()->getInt("MAX_PARTICLES"));
    pointer->start = pointer->it = vb1->getPointer();
#else
    va = new VertexArray();
    va->init();

    vb = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb->init(sizeof(Vertex) * PT::GC::get()->getInt("MAX_PARTICLES"));
    pointer->start = pointer->it = vb->getPointer();
#endif

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

    PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);

#if RENDERER_FORWARD
    vb1->releasePointer();

    vb2 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb2->init(sizeof(Vertex) * PT::GC::get()->getInt("MAX_PARTICLES"));

    vb1->bind();

    vaU->setVertexLayout(vbl);

    vaR = new VertexArray();
    vaR->init();
    vaR->setVertexLayout(vbl);

    vb1->bind();

    vaR->setVertexLayout(vbl);
#else
    vb->releasePointer();

    vb->bind();
    va->setVertexLayout(vbl);
#endif

    return true;
}

void GL::Renderer::clear()
{
    PROFILE_FUNCTION;

    glm::vec4 clear = PT::GC::get()->getVec4("CLEAR_COLOR");
    GLCheck(glClearColor(clear.r, clear.g, clear.b, clear.a));
    GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::Renderer::update()
{
    PROFILE_FUNCTION;

    static float dt = 0.0f;

#if RENDERER_FORWARD
    programs->use(UPDATE);
    vaU->use(1);
    programs->get_active(UPDATE)->setFloat("dt", dt);

    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vb2->getID());
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, pointer->size - 1);
    glEndTransformFeedback();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();

    glDisable(GL_RASTERIZER_DISCARD);

    std::swap(vb1, vb2);
#else

    vb->bind();
    auto it = vb->getPointer();

    for (int i = 0; i < pointer->size; i++)
    {
        glm::vec3 pos = it->position;

        pos.x += sin(dt);
        pos.y += sin(dt);
        pos.z += sin(dt);

        it->position = pos;
        it++;
    }

    vb->releasePointer();

#endif

    glBindVertexArray(0);
    dt += 0.001;
}

void GL::Renderer::draw()
{
    PROFILE_FUNCTION;

    this->update();

    programs->use(RENDER);

    modelMatrix();
    viewMatrix();
    projectionMatrix();

#if RENDERER_FORWARD
    vaR->use(1);
#else
    va->use(1);
#endif

    GLCheck(glDrawArrays(GL_POINTS, 0, pointer->size - 1));
}

void GL::Renderer::modelMatrix()
{
    PROFILE_FUNCTION;

    model = glm::mat4(1.0f);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    programs->get_active(RENDER)->setMat4("model", model);
}

void GL::Renderer::viewMatrix()
{
    PROFILE_FUNCTION;

    programs->get_active(RENDER)->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
}

void GL::Renderer::projectionMatrix()
{
    PROFILE_FUNCTION;

    programs->get_active(RENDER)->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());
}

void GL::Renderer::addParticle(int num)
{
    PROFILE_FUNCTION;

#if RENDERER_FORWARD
    vb1->bind();
    pointer->it = vb1->getPointer() + pointer->size - 1;
#else
    vb->bind();
    pointer->it = vb->getPointer() + pointer->size - 1;
#endif

    for (int i = 0; i < num; ++i)
    {
        if (pointer->size >= PT::GC::get()->getInt("MAX_PARTICLES"))
            break;

        pointer->it->position = glm::vec3(rand() % 8000 - 4000, rand() % 8000 - 4000, rand() % 5000 - 2500);
        pointer->it->colour = Colour::BLUE;
        pointer->it++;
        pointer->size++;
    }

#if RENDERER_FORWARD
    vb1->releasePointer();
#else
    vb->releasePointer();
#endif

    PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);
}