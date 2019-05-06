#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GL
{
    class IndexBuffer
    {
    private:
        unsigned int ID;
        unsigned int count;

    public:
        IndexBuffer(const unsigned int* _data, unsigned int _count, int _draw = GL_STATIC_DRAW);
        ~IndexBuffer();

        inline unsigned int getCount() { return count; }
        void bind() const;
        void unbind() const;
    };
} // GL

#endif /* INDEXBUFFER_H */
