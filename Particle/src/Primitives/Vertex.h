#ifndef VERTEX_H
#define VERTEX_H

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

#endif /* VERTEX_H */