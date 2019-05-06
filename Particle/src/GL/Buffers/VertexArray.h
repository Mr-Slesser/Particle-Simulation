#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

namespace GL
{
    class VertexArray
    {
    private:
        unsigned int ID;

    public:
        VertexArray();
        ~VertexArray();

        void addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
        void bind() const;
        void unbind() const;
    };
    
} // GL

#endif /* VERTEXARRAY_H */
