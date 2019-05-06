#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GL
{
    class VertexBuffer 
    {
    private:
        unsigned int ID;

    public:
        VertexBuffer(const void* _data, unsigned int _size, int _draw = GL_STATIC_DRAW);
        ~VertexBuffer();

        void bind() const;
        void unbind() const;
    };  
} // GL

#endif /* VERTEXBUFFER_H */
