#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "../Primitives/Vertex.h"
#include "VertexData.h"

namespace GL
{
struct VBPointer
{
    Vertex *start;
    Vertex *it;
    unsigned int size;
};

class VertexBuffer
{
private:
    unsigned int ID;
    unsigned long size;
    GLenum usage;

public:
    VertexBuffer(GLenum _usage);
    ~VertexBuffer();

    void init(const unsigned long &_size);
    void init(const unsigned long &_size, VertexData &vd);

    void bind();

    Vertex *getPointer();
    void releasePointer();

    unsigned int getID() const { return ID; }
};

} // namespace GL

#endif /* VERTEXBUFFER_H */
