#include "PCHeader.h"
#include "MeshRenderer.h"

namespace GL
{

MeshRenderer::MeshRenderer()
{

}

MeshRenderer::~MeshRenderer()
{

}
bool MeshRenderer::init(ProgramManager *_programs, MeshDatastore *_datastore)
{
  PROFILE("MeshRenderer::init");

  programs = _programs;
  datastore = _datastore;

  Cube c;
  rd = new ModelRenderData(c.vertices, 36, c.indices, 6 * 6, 6);

  return true;
}

void MeshRenderer::draw()
{
  PROFILE("MeshRenderer::draw");

  programs->use(RENDER_MESH);

  Camera *camera = Window::instance->GetCamera();

  programs->get_active(RENDER_MESH)->setMat4("view", camera->View());
  programs->get_active(RENDER_MESH)->setMat4("projection", camera->Projection(Window::instance->AspectRatio()));

  programs->get_active(RENDER_MESH)->setVec3("lightPosition", 0.0f, 100.0f, 0.0f);
  programs->get_active(RENDER_MESH)->setVec3("cameraPosition",camera->Position());

  datastore->bindRenderArray();
  datastore->bindVertexBuffer();

  programs->get_active(RENDER_MESH)->setMat4("model", glm::mat4(1.0f));
  glDrawElements(GL_TRIANGLES, 0, datastore->getIndicesSize());

  rd->bindRenderArray();
  rd->bindVertexBuffer();

  glm::mat4 m = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, -20.0f, 20.0f));
  m = glm::rotate(m, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  for(auto &t : rd->GetTranslations())
  {
	glm::mat4 modelMatrix = glm::translate(m, t);
	programs->get_active(RENDER_MESH)->setMat4("model", modelMatrix);
	glDrawArrays(GL_TRIANGLES, 0, rd->getVerticesCount());
  }
}
}