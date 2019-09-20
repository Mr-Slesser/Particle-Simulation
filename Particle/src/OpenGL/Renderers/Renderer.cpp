#include "PCHeader.h"
#include "Renderer.h"

GL::Renderer::Renderer()
{
}

GL::Renderer::~Renderer()
{
}

bool GL::Renderer::init(ProgramManager *_programs, Datastore *_datastore, PT::Simulation *_simulation)
{
  PROFILE("Renderer::init");

  programs = _programs;
  simulation = _simulation;
  datastore = _datastore;

  textureBuffers[0] = new TextureBuffer(GL_TEXTURE0, simulation->Force(0));
  textureBuffers[1] = new TextureBuffer(GL_TEXTURE1, simulation->Force(1));

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

  programs->use(UPDATE);
  datastore->bindUpdateArray();

  textureBuffers[0]->loadData();
  textureBuffers[0]->bindTexture();
  textureBuffers[1]->loadData();
  textureBuffers[1]->bindTexture();

  programs->get_active(UPDATE)->setFloat("dt", (float) dt);
  programs->get_active(UPDATE)->setInt("tbo_id0", 0);
  programs->get_active(UPDATE)->setInt("tbo_id1", 1);

  simulation->PrepareDraw(programs->get_active(UPDATE));

  GLCheck(glEnable(GL_RASTERIZER_DISCARD));
  GLCheck(glBindBufferBase(GL_TRANSFORM_FEEDBACK_BUFFER, 0, datastore->getSubVertexBufferID()));
  GLCheck(glBeginTransformFeedback(GL_POINTS));
  GLCheck(glDrawArrays(GL_POINTS, 0, datastore->getPointerSize()));
  GLCheck(glEndTransformFeedback());
  GLCheck(glFlush());
  GLCheck(glDisable(GL_RASTERIZER_DISCARD));

  datastore->swapBuffers();
  datastore->unbindUpdateArray();
}

void GL::Renderer::draw(double dt)
{
  PROFILE("Renderer::draw");

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