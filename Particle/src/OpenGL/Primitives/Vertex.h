#ifndef VERTEX_H
#define VERTEX_H

#include "../Buffers/VBOLayout.h"

struct CVertex
{
  glm::vec3 position;
  glm::vec4 colour;
  glm::vec3 normal;

  static GL::VBOLayout GetLayout()
  {
	GL::VBOLayout layout;
	layout.push<float>(3, 0); // Position
	layout.push<float>(4, 1); // Colour
	layout.push<float>(3, 1); // Normal
	return layout;
  }
};

struct Vertex
{
    glm::vec3 position;
    glm::vec4 colour;

  static GL::VBOLayout GetLayout()
  {
	GL::VBOLayout layout;
	layout.push<float>(3, 1); // Position
	layout.push<float>(4, 1); // Colour
	return layout;
  }
};

struct TVertex
{
    glm::vec3 position;
    glm::vec4 colour;
    glm::vec2 texcoords;

  static GL::VBOLayout GetLayout()
  {
	GL::VBOLayout layout;
	layout.push<float>(3, 1); // Position
	layout.push<float>(4, 1); // Colour
	layout.push<float>(2, 1); // Tex Coords
	return layout;
  }
};

struct MVertex
{
  glm::vec3 position;
  glm::vec4 colour;
  glm::vec3 normals;

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