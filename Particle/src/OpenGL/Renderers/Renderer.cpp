#include "PCHeader.h"
#include "Renderer.h"

GL::Renderer::Renderer()
{
}

GL::Renderer::~Renderer()
{
    programs = nullptr;
    forces = nullptr;
    datastore = nullptr;
    glDeleteBuffers(1, &texBufferID);
}

bool GL::Renderer::init(ProgramManager *_programs, Datastore *_datastore, PT::ForceGrid *_forces)
{
    programs = _programs;
    forces = _forces;
    datastore = _datastore;

    /* -------------------- TEXTURE BUFFER OBJECT ----------------------------- */
    glGenBuffers(1, &texBufferID); // Texture Buffer
    glBindBuffer(GL_TEXTURE_BUFFER, texBufferID);
    glBufferData(GL_TEXTURE_BUFFER, forces->size(), forces->data().data(), GL_DYNAMIC_DRAW);
    glGenTextures(1, &texBufferTextureID);
    glBindTexture(GL_TEXTURE_BUFFER, texBufferTextureID);
    glTexBuffer(GL_TEXTURE_BUFFER, GL_RGB32F, texBufferID);
    /* ------------------------------------------------------------------------ */

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
    datastore->bindUpdateArray();

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
    glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, datastore->getSubVertexBufferID());
    glBeginTransformFeedback(GL_POINTS);
    glDrawArrays(GL_POINTS, 0, datastore->getPointerSize());

    glEndTransformFeedback();
    datastore->unbindSubVertexBuffer();
    glFlush();
    glDisable(GL_RASTERIZER_DISCARD);

    datastore->swapBuffers();
    datastore->unbindUpdateArray();

    dt += 0.001;
}

void GL::Renderer::draw()
{
    if (datastore->getPointerSize() > 0)
    {
        this->update();
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
    model = glm::mat4(1.0f);
    programs->get_active(RENDER)->setMat4("model", model);
    programs->get_active(RENDER)->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
    programs->get_active(RENDER)->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());
}

// TODO: Move this elsewhere.
void GL::Renderer::addParticle(int num)
{
    std::vector<PT::ParticleData> a;

    auto grid = forces->getGridData();
    float sizeX = grid.x * grid.z;
    float sizeY = grid.y * grid.w;

    for (int i = 0; i < num; ++i)
    {
        PT::ParticleData v;
        v.position = glm::vec3(Utils::Random::ZeroToOne() * sizeX, -Utils::Random::ZeroToOne() * sizeY, 0.0f);
        v.velocity = glm::vec3(Utils::Random::ZeroToOne(), -Utils::Random::ZeroToOne(), 0.0f);
        v.colour = Colour::RED;

        v.lifespan = 1.0f;
        v.mass = 1.0f;
        a.push_back(v);
    }

    datastore->submitData(a);
}