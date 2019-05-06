#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "./Vertex.hpp"

struct Triangle 
{
    Vertex A;
    Vertex B;
    Vertex C;

    Triangle()
        : A({}), B({}), C({}) {}
    Triangle(Vertex& a, Vertex& b, Vertex& c)
        : A(a), B(b), C(x) {}
};

#endif /* TRIANGLE_HPP */
