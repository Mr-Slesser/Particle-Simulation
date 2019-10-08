#ifndef PARTICLE_PARTICLE_SRC_OPENGL_PRIMITIVES_PLANE_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_PRIMITIVES_PLANE_H_

#include "Vertex.h"

 class Plane : public Object, public GL::Renderable
{
 protected:
	unsigned int resolution;
   	std::vector<Vertex> vertices;
   	std::vector<unsigned int> indices;

 public:
  Plane(float x, float y, float z, float width, float height, float depth, unsigned int _resolution = 20);
  virtual ~Plane();
  virtual void Generate();
};

#endif //PARTICLE_PARTICLE_SRC_OPENGL_PRIMITIVES_PLANE_H_
