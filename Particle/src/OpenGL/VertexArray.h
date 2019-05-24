#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include <vector>

#include "OpenGL.h"

#include "VertexData.h"
#include "VertexBuffer.h"
#include "VBOLayout.h"

#include "../Primitives/Quad.h"
#include "../Primitives/Cube.h"

namespace GL {

    class VertexArray {
    public:
        VertexArray();
        virtual ~VertexArray();


        void initBuffers(const unsigned long& size);

        void use();
        void bindVBO();

        VertexBuffer* getBuffer() { return buffers.front(); }

    private:
        unsigned int ID;

        std::vector<VertexBuffer*> buffers;

        void setVertexLayout(VBOLayout& vbol);
    };

} // namespace GL

#endif /* VERTEXARRAY_H */
