#ifndef PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_MODELRENDERDATA_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_MODELRENDERDATA_H_

#include "./RenderData.h"

namespace GL
{

class ModelRenderData: public RenderData<CVertex>
{
 private:
  unsigned int instances;
  std::vector<glm::vec3> translations;

 public:
  ModelRenderData(CVertex *data, unsigned int numData, unsigned int *indices, unsigned int numIndex, unsigned int instanceCount);
  virtual void Init() override;

  inline const std::vector<glm::vec3> &GetTranslations() const { return translations; }
};

}

#endif //PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_MODELRENDERDATA_H_
