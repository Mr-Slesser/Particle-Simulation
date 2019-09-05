#include "PCHeader.h"
#include "Renderer.h"

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
    programs = nullptr;
    forces = nullptr;

    delete va;
    delete pointer;

    delete vb1;
    delete vb2;
    delete vaR;
    delete vaU;

    glDeleteBuffers(1, &texBufferID);
}

bool GL::Renderer::init(ProgramManager *_programs, PT::ForceGrid *_forces)
{
    programs = _programs;
    forces = _forces;

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3, 0); // Position
    vbl.push<float>(3, 0); // Velocity
    vbl.push<float>(4, 1); // Colour
    vbl.push<float>(1, 1); // Lifespan
    vbl.push<float>(1, 1); // Mass

    vaU = new VertexArray();
    vaU->init();

    /* -------------------- TEXTURE BUFFER OBJECT ----------------------------- */
    glGenBuffers(1, &texBufferID); // Texture Buffer
    glBindBuffer(GL_TEXTURE_BUFFER, texBufferID);
    glBufferData(GL_TEXTURE_BUFFER, forces->size(), forces->data().data(), GL_DYNAMIC_DRAW);
    glGenTextures(1, &texBufferTextureID);
    glBindTexture(GL_TEXTURE_BUFFER, texBufferTextureID);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, texBufferID);
    /* ------------------------------------------------------------------------ */

    vb1 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb1->init(sizeof(PT::ParticleData) * MAX_PARTICLES);
    // vb1->init(sizeof(Vertex) * MAX_PARTICLES);
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
            pointer->it->velocity = glm::vec3(0.0f, 0.0f, 0.0f);
            pointer->it->colour = Colour::PINK;
            pointer->it->lifespan = 1.0f;
            pointer->it->mass = 1.0f;
            pointer->it++;
            pointer->size++;
        }
    }

    PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);

    vb1->releasePointer();

    vb2 = new VertexBuffer(GL_DYNAMIC_DRAW);
    vb2->init(sizeof(PT::ParticleData) * MAX_PARTICLES);
    // vb2->init(sizeof(Vertex) * MAX_PARTICLES);

    vb1->bind();

    vaU->setVertexLayout(vbl);

    vaR = new VertexArray();
    vaR->init();
    vaR->setVertexLayout(vbl);

    vb1->bind();

    vaR->setVertexLayout(vbl);

    
    vaR->unbind();

    return true;
}

void GL::Renderer::clear()
{
    glm::vec4 clear = PT::GC::get()->getVec4("CLEAR_COLOR");
    GLCheck(glClearColor(clear.r, clear.g, clear.b, clear.a));
    GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::Renderer::update()
{
    static float dt = 0.0f;

    programs->use(UPDATE);
    vaU->use(1);

    /* -------------------- TEXTURE BUFFER OBJECT ----------------------------- */
    GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, texBufferID));
    auto tpointer = (glm::vec3 *)glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
    memcpy(tpointer, forces->data().data(), forces->size());
    GLCheck(glUnmapBuffer(GL_TEXTURE_BUFFER));
    glBindTexture(GL_TEXTURE_BUFFER, texBufferTextureID);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, texBufferID);
    /* ------------------------------------------------------------------------ */

    glActiveTexture(GL_TEXTURE0);
    programs->get_active(UPDATE)->setFloat("dt", dt);
    programs->get_active(UPDATE)->setInt("tbo_id", 0);
    forces->setGridData(programs->get_active(UPDATE));

    glEnable(GL_RASTERIZER_DISCARD);
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, vb2->getID());
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, pointer->size - 1);
    glEndTransformFeedback();
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glFlush();

    glDisable(GL_RASTERIZER_DISCARD);

    std::swap(vb1, vb2);

    vaU->unbind();
    dt += 0.001;
}

void GL::Renderer::draw()
{
    this->update();

    programs->use(RENDER);

    MVP();
    vaR->use(1);

    GLCheck(glDrawArrays(GL_POINTS, 0, pointer->size - 1));

    vaR->unbind();
}

void GL::Renderer::MVP()
{
    model = glm::mat4(1.0f);
    //model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(0.5f, 1.0f, 0.0f));
    programs->get_active(RENDER)->setMat4("model", model);
    programs->get_active(RENDER)->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
    programs->get_active(RENDER)->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());
}

void GL::Renderer::addParticle(int num)
{
    std::vector<PT::ParticleData> a;
    for (int i = 0; i < num; ++i)
    {
        PT::ParticleData v;
        v.position = glm::vec3(rand() % 200 - 100, rand() % 200 - 100, rand() % 20 - 10);
        v.velocity = glm::vec3(1.0f, 1.0f, 1.0f);
        v.colour = Colour::GREEN;
        v.lifespan = 1.0f;
        v.mass = 1.0f;
        a.push_back(v);
    }

    submitData(a);
}

void GL::Renderer::submitData(std::vector<PT::ParticleData> &data)
{
    auto maxSize = PT::GC::get()->getInt("MAX_PARTICLES");
    if (pointer->size - 1 + data.size() > maxSize)
        data.resize(maxSize - (pointer->size - 1) - 1);

    if (data.size() == 0)
    {
        return;
    }
    else
    {
        vb1->bind();
        pointer->it = vb1->getPointer() + pointer->size - 1;

        memcpy(pointer->it, data.data(), data.size() * sizeof(PT::ParticleData));
        pointer->size += data.size();
        vb1->releasePointer();

        PT::GC::get()->updateInt("CURR_NO_PARTICLES", pointer->size);
    }
}