#ifndef VERTEX_H
#define VERTEX_H

#include "../Buffers/VBOLayout.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec4 colour;
};

struct TVertex
{
    glm::vec3 position;
    glm::vec4 colour;
    glm::vec2 texcoords;
};

struct MVertex
{
  glm::vec3 position;
  glm::vec4 colour;
  glm::vec3 normals;
};

struct CVertex
{
  float position[3];
  float colour[4];
  float normal[3];

  static GL::VBOLayout GetLayout()
  {
	GL::VBOLayout layout;
	layout.push<float>(3, 1); // Position
	layout.push<float>(4, 1); // Colour
	layout.push<float>(3, 1); // Normal
	return layout;
  }
};

#endif /* VERTEX_H */