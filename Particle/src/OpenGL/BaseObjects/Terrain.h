#ifndef PARTICLE_PARTICLE_SRC_OPENGL_BASEOBJECTS_TERRAIN_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_BASEOBJECTS_TERRAIN_H_

#include "../Primitives/Plane.h"

class Terrain : public Plane
{
 private:
  std::vector<float> maxHeightThresholds;

 public:
  Terrain(float x, float y, float z, float width, float height, float depth, unsigned int _resolution = 20);
  virtual ~Terrain();
  virtual void Generate() override;

  virtual void GenerateHeightThresholds();
};
#endif //PARTICLE_PARTICLE_SRC_OPENGL_BASEOBJECTS_TERRAIN_H_
