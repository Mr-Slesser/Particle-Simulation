#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "glad/glad.h"
#include "GLFW/glfw3.h"

// TODO: Predefined colours.

struct Position {
    float x;
    float y;
    float z;

    Position() 
        : x(0.0f), y(0.0f), z(0.0f) {}
    Position(float& _x, float& _y, float& _z)
        : x(_x), y(_y), z(_z) {}
};

struct Colour {
    unsigned char r, g, b, a;

    Colour() 
        : r(255), g(255), b(255), a(255) {}
    Colour(unsigned char _r, unsigned char _g, unsigned char _b, unsigned char _a) 
        : r(_r), g(_g), b(_b), a(_a) {}
};

struct Vertex {
    Position p;
    Colour c;

    Vertex()
        : p({}), c({}) {}
    Vertex(Position _p, Colour _c)
        : p(_p), c(_c) {}
};

#endif /* VERTEX_HPP */
