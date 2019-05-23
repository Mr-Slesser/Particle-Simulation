#ifndef QUAD_H
#define QUAD_H

#include "Vertex.h"

struct Quad {
    Vertex vertices[4] = {
        {{ 1.0f,  1.0f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}}, // Top right
        {{ 1.0f, -1.0f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}}, // Bottom right
        {{-1.0f, -1.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}}, // Bottom left
        {{-1.0f,  1.0f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}  // Top left 
    };

    unsigned int indices[6] = {
        0, 1, 3,
        1, 2, 3
    };
};

#endif /* QUAD_H */