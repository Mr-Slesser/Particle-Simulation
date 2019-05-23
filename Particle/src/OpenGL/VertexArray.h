#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "OpenGL.h"

#include "../Primitives/Quad.h"

namespace GL {

    class VertexArray {
    public:
        VertexArray();
        virtual ~VertexArray();

        void initBuffers(Quad& q);

        void use();

    private:
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;
    };

} // namespace GL

#endif /* VERTEXARRAY_H */
