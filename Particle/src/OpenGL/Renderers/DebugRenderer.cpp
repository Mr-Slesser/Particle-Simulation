#include "PCHeader.h"
#include "DebugRenderer.h"

namespace GL
{
DebugRenderer::DebugRenderer()
{
}

DebugRenderer::~DebugRenderer()
{
}

bool DebugRenderer::Init(std::shared_ptr<ProgramManager> _programs, std::shared_ptr<DebugData> _datastore)
{
    PROFILE("DebugRenderer::init");

    programs = _programs;
	datastore = _datastore;

	return true;
}

void DebugRenderer::Draw()
{
    PROFILE("DebugRenderer::draw");

    programs->Use(RENDER_DEBUG);
	datastore->Bind();

	Camera *camera = Window::instance->GetCamera();
    programs->Active()->Mat4("model", glm::mat4(1.0f));
	programs->Active()->Mat4("view", camera->View());
	programs->Active()->Mat4("projection", camera->Projection(Window::instance->AspectRatio()));

    GLCheck(glDrawArrays(GL_LINES, 0, datastore->Size()));
}

} // namespace GL