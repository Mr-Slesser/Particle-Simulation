#include "PCHeader.h"
#include "ModelRenderData.h"

GL::ModelRenderData::ModelRenderData(CVertex *data, unsigned int numData, unsigned int *indices, unsigned int numIndex, unsigned int instanceCount)
	: RenderData(data, numData, indices, numIndex), instances(instanceCount)
{
	Init();
}

void GL::ModelRenderData::Init()
{
  // Base translation...
  translations.push_back(glm::vec3(0.5f, -0.5f, 0.5f));

  // The other translations...
  for (int i = 1; i < instances; ++i)
  {
	translations.push_back(glm::vec3(0.5f + i * 1.5f, -0.5f, 0.5f + i * 1.5f));
  }
}
