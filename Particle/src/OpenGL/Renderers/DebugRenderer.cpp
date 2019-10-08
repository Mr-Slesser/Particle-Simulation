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

bool DebugRenderer::init(ProgramManager *_programs, DebugDatastore *_datastore, PT::Simulation *_simulation, TextureBuffer *_tb)
{
    PROFILE("DebugRenderer::init");

    programs = _programs;
	simulation = _simulation;
	datastore = _datastore;
    forces = simulation->Force(0);
  	textureBuffer = _tb;

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

void DebugRenderer::draw()
{
    PROFILE("DebugRenderer::draw");

//    auto data = datastore->getElements();
    programs->use(RENDER_DEBUG);

    VA->bind();
    VB->bind();

//	textureBuffer->loadData();
	textureBuffer->bindTexture();

	programs->get_active(RENDER_DEBUG)->setInt("tbo_id0", 0);

	Camera *camera = Window::instance->GetCamera();

    programs->get_active(RENDER_DEBUG)->setMat4("model", glm::mat4(1.0f));
	programs->get_active(RENDER_DEBUG)->setMat4("view", camera->View());
	programs->get_active(RENDER_DEBUG)->setMat4("projection", camera->Projection(Window::instance->AspectRatio()));
  	simulation->PrepareDebugDraw(programs->get_active(RENDER_DEBUG));

    GLCheck(glDrawArrays(GL_POINTS, 0, datastore->dataSize()));
	VB->unbind();
    VA->unbind();
}

} // namespace GL