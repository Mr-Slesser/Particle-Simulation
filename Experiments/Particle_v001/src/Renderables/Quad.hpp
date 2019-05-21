#ifndef QUAD_HPP
#define QUAD_HPP

#include "./Vertex.hpp"

namespace PT {

    struct Quad
    {
        Vertex vertices[4] = {
            {{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
            {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f, 0.0f}, {1.0f, 0.0f, 1.0f, 1.0f}, {0.0f, 1.0f}}
        };

    };

} // namespace PT

#endif /* QUAD_HPP */