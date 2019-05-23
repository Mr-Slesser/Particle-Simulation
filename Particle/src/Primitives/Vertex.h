#ifndef VERTEX_H
#define VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct Vertex {
    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec4 colour = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f);
};

struct TVertex {
    glm::vec3 position;
    glm::vec4 colour;
    glm::vec2 texcoords;
}; 

#endif /* VERTEX_H */