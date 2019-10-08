#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "VertexBuffer.h"
#include "VBOLayout.h"

namespace GL
{

class VertexArray
{
public:
    VertexArray();
    virtual ~VertexArray();

    void init();

    void bind();
    void unbind();

    void setVertexLayout(VBOLayout vbol);

private:
    unsigned int ID;
};

} // namespace GL

#endif /* VERTEXARRAY_H */
