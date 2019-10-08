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


//  glm::mat4 m = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, -20.0f, 20.0f));
//  m = glm::translate(m, glm::vec3(0.5f, -0.5f, 0.5f));
//
//  programs->get_active(RENDER_MESH)->setMat4("model", m);
  programs->get_active(RENDER_MESH)->setMat4("view", PT::CameraManager::get()->getCamera()->getLookAt());
  programs->get_active(RENDER_MESH)->setMat4("projection", PT::CameraManager::get()->getCamera()->getProjection());

//  programs->get_active(RENDER_MESH)->setMat4("view", glm::mat4(1.0f));
//  programs->get_active(RENDER_MESH)->setMat4("projection", glm::mat4(1.0f));

  programs->get_active(RENDER_MESH)->setVec3("lightPosition", 0.0f, 100.0f, 0.0f);
  programs->get_active(RENDER_MESH)->setVec3("cameraPosition", PT::CameraManager::get()->getCamera()->getPosition());

//  datastore->bindRenderArray();
//  datastore->bindVertexBuffer();

//  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//  GLCheck(glDrawArrays(GL_TRIANGLES, 0, datastore->getVerticesCount()));
//  glDrawElements(GL_TRIANGLES, datastore->getIndicesSize(), GL_UNSIGNED_INT, nullptr);
//  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

  rd->bindRenderArray();
  rd->bindVertexBuffer();

  glm::mat4 m = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, -20.0f, 20.0f));
  m = glm::rotate(m, glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
  for(auto &t : rd->GetTranslations())
  {
	glm::mat4 model = glm::translate(m, t);
	programs->get_active(RENDER_MESH)->setMat4("model", model);
	glDrawArrays(GL_TRIANGLES, 0, rd->getVerticesCount());
  }
}
}