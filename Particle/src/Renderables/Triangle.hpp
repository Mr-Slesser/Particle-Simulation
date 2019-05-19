#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "./Vertex.hpp"

namespace PT {

    struct Triangle
    {
        Vertex vertices[3] = {
            {{ 0.5f,  0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{ 0.5f, -0.5f, 0.0f}, {0.0f, 1.0f, 1.0f, 1.0f}},
            {{-0.5f, -0.5f, 0.0f}, {1.0f, 1.0f, 1.0f, 1.0f}}
        };
    };

} // namespace PT

#endif // TRIANGLE_HPP