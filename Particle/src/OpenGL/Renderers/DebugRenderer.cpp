#include "PCHeader.h"
#include "DebugRenderer.h"

namespace GL
{
DebugRenderer::DebugRenderer()
{
}

DebugRenderer::~DebugRenderer()
{
    delete VA;
    delete VB;
}

bool DebugRenderer::init(ProgramManager *_programs, DebugDatastore *_datastore, PT::Simulation *_simulation)
{
    PROFILE("DebugRenderer::init");

    programs = _programs;
	simulation = _simulation;
	datastore = _datastore;
    forces = simulation->Force(0);

    GL::VBOLayout vbl = VBOLayout();
    vbl.push<float>(3, 0); // Position
    vbl.push<float>(4, 0); // Colour

    VA = new VertexArray();
    VA->init();

    VB = new VertexBuffer<PT::ParticleData>(GL_DYNAMIC_DRAW);
    VB->init(sizeof(DebugDatastoreElement) * 1000000);

    VA->setVertexLayout(vbl);

  	auto data = datastore->getElements();
	auto datapointer = (DebugDatastoreElement *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	memcpy(datapointer, data.data(), data.size() * sizeof(DebugDatastoreElement));
	VB->releasePointer();

    VA->unbind();

    return true;
}

void DebugRenderer::draw(ForcesDatastore* forces)
{
    PROFILE("DebugRenderer::draw");

    programs->use(RENDER_DEBUG);

    VA->bind();
    VB->bind();

	programs->get_active(RENDER_DEBUG)->setInt("tbo_id0", 0);

    programs->get_active(RENDER_DEBUG)->setMat4("model", glm::mat4(1.0f));
    programs->get_active(RENDER_DEBUG)->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
    programs->get_active(RENDER_DEBUG)->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());

    forces->SetDebugUniforms(programs->get_active(RENDER_DEBUG));

    GLCheck(glDrawArrays(GL_POINTS, 0, forces->dataSize()));

	VB->unbind();
    VA->unbind();
}

} // namespace GL