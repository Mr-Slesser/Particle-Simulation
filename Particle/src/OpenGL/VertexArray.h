#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexData.h"
#include "VertexBuffer.h"
#include "VBOLayout.h"

#include "../Primitives/Quad.h"
#include "../Primitives/Cube.h"

namespace GL
{

class VertexArray
{
public:
    VertexArray();
    virtual ~VertexArray();

    void init();
    void initBuffers(const unsigned long &size);

    void use();
    void use(int a); // TODO: Temp!
    void use(VertexBuffer *vb);
    void bindVBO();
    void unbind() { glBindVertexArray(0);}

    VertexBuffer *getBuffer() { return buffers.front(); }
    void setVertexLayout(VBOLayout &vbol);

private:
    unsigned int ID;

    std::vector<VertexBuffer *> buffers;
};

} // namespace GL

#endif /* VERTEXARRAY_H */
