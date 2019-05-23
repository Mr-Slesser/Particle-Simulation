#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec4 colour;
    glm::vec2 texcoords;
};  

#endif /* VERTEX_H */
