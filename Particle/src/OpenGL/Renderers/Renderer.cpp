#include "PCHeader.h"
#include "Renderer.h"

GL::Renderer::Renderer()
{
}

GL::Renderer::~Renderer()
{
    programs = nullptr;
    datastore = nullptr;
    glDeleteBuffers(1, &texBufferID0);
    glDeleteBuffers(1, &texBufferID1);
}

bool GL::Renderer::init(ProgramManager *_programs, Datastore *_datastore, PT::Simulation *_simulation)
{
    PROFILE("Renderer::init");

    programs = _programs;
    simulation = _simulation;
    // forces0 = _forces0;
    // forces1 = _forces1;
    datastore = _datastore;

    auto forces0 = simulation->Force(0);
    auto forces1 = simulation->Force(1);

    /* -------------------- TEXTURE BUFFER OBJECT 0 ----------------------------- */
    glGenBuffers(1, &texBufferID0); // Texture Buffer
    glBindBuffer(GL_TEXTURE_BUFFER, texBufferID0);
    glBufferData(GL_TEXTURE_BUFFER, forces0->size(), forces0->getDataPointer(), GL_DYNAMIC_DRAW);
    glGenTextures(1, &texBufferTextureID0);
    glBindTexture(GL_TEXTURE_BUFFER, texBufferTextureID0);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, texBufferID0);
    /* -------------------------------------------------------------------------- */

    /* -------------------- TEXTURE BUFFER OBJECT 0 ----------------------------- */
    glGenBuffers(1, &texBufferID1); // Texture Buffer
    glBindBuffer(GL_TEXTURE_BUFFER, texBufferID1);
    glBufferData(GL_TEXTURE_BUFFER, forces1->size(), forces1->getDataPointer(), GL_DYNAMIC_DRAW);
    glGenTextures(1, &texBufferTextureID1);
    glBindTexture(GL_TEXTURE_BUFFER, texBufferTextureID1);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, texBufferID1);
    /* -------------------------------------------------------------------------- */

    return true;
}

void GL::Renderer::clear()
{
    PROFILE("Renderer::clear");

    glm::vec4 clear = PT::GC::get()->getVec4("CLEAR_COLOR");
    GLCheck(glClearColor(clear.r, clear.g, clear.b, clear.a));
    GLCheck(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void GL::Renderer::update(double dt)
{
    PROFILE("Renderer::update");

    auto forces0 = simulation->Force(0);
    auto forces1 = simulation->Force(1);

    programs->use(UPDATE);
    datastore->bindUpdateArray();

    /* -------------------- TEXTURE BUFFER OBJECT 0 ----------------------------- */
    GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, texBufferID0));
    auto tpointer0 = (glm::vec3 *)glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
    memcpy(tpointer0, forces0->getDataPointer(), forces0->size());
    GLCheck(glUnmapBuffer(GL_TEXTURE_BUFFER));
    GLCheck(glActiveTexture(GL_TEXTURE0));
    GLCheck(glBindTexture(GL_TEXTURE_BUFFER, texBufferTextureID0));
    GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, texBufferID0));
    /* ------------------------------------------------------------------------- */

    /* -------------------- TEXTURE BUFFER OBJECT 1 ----------------------------- */
    GLCheck(GLCheck(glBindBuffer(GL_TEXTURE_BUFFER, texBufferID1)));
    auto tpointer1 = (glm::vec3 *)glMapBuffer(GL_TEXTURE_BUFFER, GL_WRITE_ONLY);
    memcpy(tpointer1, forces1->getDataPointer(), forces1->size());
    GLCheck(glUnmapBuffer(GL_TEXTURE_BUFFER));
    GLCheck(glActiveTexture(GL_TEXTURE1));
    GLCheck(glBindTexture(GL_TEXTURE_BUFFER, texBufferTextureID1));
    GLCheck(glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, texBufferID1));
    /* ------------------------------------------------------------------------- */

    programs->get_active(UPDATE)->setFloat("dt", (float)dt);
    programs->get_active(UPDATE)->setInt("tbo_id0", 0);
    programs->get_active(UPDATE)->setInt("tbo_id1", 1);

    // forces0->setGridData(programs->get_active(UPDATE));
    simulation->PrepareDraw(programs->get_active(UPDATE));

    GLCheck(glEnable(GL_RASTERIZER_DISCARD));
    GLCheck(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, datastore->getSubVertexBufferID()));
    GLCheck(glBeginTransformFeedback(GL_POINTS));
    GLCheck(glDrawArrays(GL_POINTS, 0, datastore->getPointerSize()));
    GLCheck(glEndTransformFeedback());
    // datastore->unbindSubVertexBuffer();
    GLCheck(glFlush());
    GLCheck(glDisable(GL_RASTERIZER_DISCARD));

    datastore->swapBuffers();
    datastore->unbindUpdateArray();
}

void GL::Renderer::draw(double dt)
{
    PROFILE("Renderer::draw");

    auto forces0 = simulation->Force(0);
    auto forces1 = simulation->Force(1);

    if (datastore->getPointerSize() > 0)
    {
        this->update(dt);
        programs->use(RENDER);
        MVP();
        datastore->bindRenderArray();
        datastore->bindVertexBuffer();

        GLCheck(glDrawArrays(GL_POINTS, 0, datastore->getPointerSize()));

        datastore->unbindRenderArray();
    }
}

void GL::Renderer::MVP()
{
    PROFILE("Renderer::MVP");

    model = glm::mat4(1.0f);
    programs->get_active(RENDER)->setMat4("model", model);
    programs->get_active(RENDER)->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
    programs->get_active(RENDER)->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());
}

// TODO: Move this elsewhere.
void GL::Renderer::addParticle(int num)
{
    PROFILE("Renderer::addParticle");

    auto forces0 = simulation->Force(0);
    auto forces1 = simulation->Force(1);

    std::vector<PT::ParticleData> a;

    auto grid = forces0->getDimensions();
    float X = grid.x * forces0->getResolution();
    float Y = grid.y * forces0->getResolution();
    float Z = grid.z * forces0->getResolution();

    for (int i = 0; i < num; ++i)
    {
        PT::ParticleData v;
        v.position = glm::vec3(Utils::Random::ZeroToOne() * X, 0.0f, Utils::Random::ZeroToOne() * Z);
        v.velocity = glm::vec3(Utils::Random::ZeroToOne(), Utils::Random::ZeroToOne(), Utils::Random::ZeroToOne());
        v.colour = Colour::RED;

        v.lifespan = 1.0f;
        // v.mass = 1.0f;
        v.mass = Utils::Random::RandomRange(0.5f, 1.5f);
        a.push_back(v);
    }

    datastore->submitData(a);
}