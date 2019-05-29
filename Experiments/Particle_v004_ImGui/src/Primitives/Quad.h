#ifndef QUAD_H
#define QUAD_H

#include "Vertex.h"

struct Quad {
    TVertex vertices[4] = {
        {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
        {{-0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
        {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 1.0f}},
        {{ 0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, {1.0f, 1.0f}},
    };

    unsigned int indices[6] = {
        0, 1, 2,
        2, 3, 0
    };
};

#endif /* QUAD_H */
