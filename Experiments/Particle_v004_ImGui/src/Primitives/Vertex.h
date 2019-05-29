#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>

#include "./Colours.h"

struct Vertex
{
    glm::vec3 position;
    glm::vec4 colour;
};

struct TVertex {
    glm::vec3 position;
    glm::vec4 colour;
    glm::vec2 texcoords;
}; 

#endif /* VERTEX_H */