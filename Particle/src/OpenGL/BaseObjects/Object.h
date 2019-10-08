#ifndef PARTICLE_PARTICLE_SRC_OPENGL_PRIMITIVES_OBJECT_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_PRIMITIVES_OBJECT_H_

#include "OpenGL/Datastores/DebugDatastore.h"

class Object
{
 protected:
  glm::vec3 position;
  glm::vec3 dimensions;

 public:
  Object(float x, float y, float z, float w, float h, float d)
  	: position(glm::vec3(x, y, z)), dimensions(glm::vec3(w, h, d)) {}
	virtual ~Object() {}

  const glm::vec3 &Dimensions() const { return dimensions; }
  void SetDimensions(glm::ivec3 to) { dimensions = to; }
  void AddWidth(int add) { dimensions.x += add; }
  void AddHeight(int add) { dimensions.y += add; }
  void AddDepth(int add) { dimensions.z += add; }

  const glm::vec3 &Position() const { return position; }
  void SetPosition(glm::ivec3 to) { position = to; }
  void AddX(int add) { position.x += add; }
  void AddY(int add) { position.y += add; }
  void AddZ(int add) { position.z += add; }

  void SubmitDebugOutline(GL::DebugDatastore *debugData)
  {
	float x = position.x;
	float y = position.y;
	float z = position.z;

	int X = dimensions.x;
	int Y = dimensions.y;
	int Z = dimensions.z;

	// Front
	debugData->addElement({glm::vec3(x, y, z)}, {glm::vec3(x + X, y, z)}); // Bottom
	debugData->addElement({glm::vec3(x, y, z)}, {glm::vec3(0.0f, y + Y, z)}); // Left
	debugData->addElement({glm::vec3(x, y + Y, z)}, {glm::vec3(x + X, y + Y, z)}); // Top
	debugData->addElement({glm::vec3(x + X, y, z)}, {glm::vec3(x + X, y + Y, z)}); // Right

	// Back
	debugData->addElement({glm::vec3(x, y, z + Z)}, {glm::vec3(x + X, y, z + Z)}); // Bottom
	debugData->addElement({glm::vec3(x, y, z + Z)}, {glm::vec3(x, y + Y, z + Z)}); // Left
	debugData->addElement({glm::vec3(x, y + Y, z + Z)}, {glm::vec3(X, y + Y, z + Z)}); // Top
	debugData->addElement({glm::vec3(x + X, y, z + Z)}, {glm::vec3(X, y + Y, z + Z)}); // Right

	// Connections
	debugData->addElement({glm::vec3(x, y + Y, z)}, {glm::vec3(x, y + Y, z + Z)}); // Top Left
	debugData->addElement({glm::vec3(x + X, y + Y, z)}, {glm::vec3(x + X, y + Y, z + Z)}); // Top Right
	debugData->addElement({glm::vec3(x, y, z)}, {glm::vec3(x, y, z + Z)}); // Bottom Left
	debugData->addElement({glm::vec3(x + X, y, z)}, {glm::vec3(x + X, y, z + Z)}); // Bottom Right
  }
};

#endif //PARTICLE_PARTICLE_SRC_OPENGL_PRIMITIVES_OBJECT_H_
