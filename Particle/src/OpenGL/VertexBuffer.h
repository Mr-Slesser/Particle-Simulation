#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "../Particle/Particle.h"
#include "../Primitives/Vertex.h"
#include "VertexData.h"

namespace GL
{
struct VBPointer
{
    PT::ParticleData *start;
    PT::ParticleData *it;
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

    PT::ParticleData *getPointer();
    void releasePointer();

    unsigned int getID() const { return ID; }
};

} // namespace GL

#endif /* VERTEXBUFFER_H */
