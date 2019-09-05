#include "PCHeader.h"
#include "DebugRenderer.h"

namespace GL
{
DebugRenderer::DebugRenderer()
{
}

DebugRenderer::~DebugRenderer()
{
    // programs = nullptr;
    // forces = nullptr;

    delete VA;
    delete VB;
}

bool DebugRenderer::init(ProgramManager *_programs, PT::ForceGrid *_forces)
{
    programs = _programs;
    forces = _forces;

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3, 0); // Position
    vbl.push<float>(4, 0); // Colour

    VA = new VertexArray();
    VA->init();

    VB = new VertexBuffer(GL_DYNAMIC_DRAW);
    VB->init(sizeof(DebugDataElement) * 100000);

    VA->setVertexLayout(vbl);

    VA->unbind();

    return true;
}

void DebugRenderer::draw(DebugData *datastore)
{
    auto data = datastore->getElements();
    programs->use(RENDER_DEBUG);

    VA->use(1);
    VB->bind();
    auto datapointer = (DebugDataElement*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    memcpy(datapointer, data.data(), data.size() * sizeof(DebugDataElement));
    VB->releasePointer();

    programs->get_active(RENDER_DEBUG)->setMat4("model", glm::mat4(1.0f));
    programs->get_active(RENDER_DEBUG)->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
    programs->get_active(RENDER_DEBUG)->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());

    GLCheck(glDrawArrays(GL_LINES, 0, data.size()));

    GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
    VA->unbind();
}

} // namespace GL