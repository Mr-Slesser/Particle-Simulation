#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
    float position[3];
    float colour[4];
    float tex[2];
    glm::mat4 model = glm::mat4(1.0f);
};

#endif /* VERTEX_HPP */

// TODO: Add VBLayout to these