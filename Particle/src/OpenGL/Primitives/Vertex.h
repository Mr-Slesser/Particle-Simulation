#ifndef VERTEX_H
#define VERTEX_H

#include "../Buffers/VBOLayout.h"

struct Vertex
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

struct DebugVertex
{
  glm::vec3 position;
  glm::vec4 colour = Colour::WHITE;

  static GL::VBOLayout GetLayout()
  {
	GL::VBOLayout layout;
	layout.push<float>(3, 0); // Position
	layout.push<float>(4, 1); // Colour
	return layout;
  }
};

#endif /* VERTEX_H */