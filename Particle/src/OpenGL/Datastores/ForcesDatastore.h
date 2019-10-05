#ifndef PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_FORCESDATASTORE_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_FORCESDATASTORE_H_

#include "../Programs/ProgramManager.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/UpdateTBO.h"
#include "../Buffers/NoiseTBO.h"

namespace GL
{

struct ForceData
{
  std::vector<int> P;
  glm::vec3 Dimensions;
  glm::vec2 Resolution;
  int Octaves = 5;
  float Persistance = 0.6f;

  ForceData(std::vector<int> p, glm::vec3 dimensions, glm::vec2 resolution)
	  : P(p), Dimensions(dimensions), Resolution(resolution) {}
};

class ForcesDatastore
{
 private:
  bool showActualMagnitude = true;
  float maxMagnitude = 1.0f;

  std::mutex mutex;
  ProgramManager *programs;
  ForceData *data;
  VertexBuffer<glm::vec3> *VBO;
  VertexArray *VAO;
  VBPointer<glm::vec3> *pointer;

  NoiseTBO *Noise;
  UpdateTBO *TBO;

 public:
  ForcesDatastore(ProgramManager *_programs, glm::vec3 dimensions, glm::vec2 resolution, GL::DebugDatastore *_debugData);
  virtual ~ForcesDatastore();

  void Init(ProgramManager *_programs, GL::DebugDatastore *_debugData);
  void Update(double dt);
  void SetDebugUniforms(Program *program);

  void bindUpdateArray();
  void bindVertexBuffer();
  void bindTextureBuffer() { TBO->bindTexture(); }

  inline void setOctaves(int o) { data->Octaves = o; }
  inline void setPersistance(float p) { data->Persistance = p; }

  int dataSize() { return pointer->size; }

  inline int getOctaves() { return data->Octaves; }
  inline float getPersistance() { return data->Persistance; }

  inline glm::vec3 getDimensions() { return data->Dimensions; }
  inline glm::vec2 getResolution() { return data->Resolution; }

  bool isShowingActualMagnitude() { return showActualMagnitude; }
  void setShowActualMagnitude(bool to) { showActualMagnitude = to; }

  float getMaxMagnitude() { return maxMagnitude; }
  void setMaxMagnitude(float to ) {  maxMagnitude = to; }
};
}

#endif //PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_FORCESDATASTORE_H_
