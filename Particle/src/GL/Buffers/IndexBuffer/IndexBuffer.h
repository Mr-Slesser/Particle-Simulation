#ifndef IndexBuffer_H
#define IndexBuffer_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace GL
{
    class IndexBuffer
    {
    protected:
        unsigned int ID;
        unsigned int count;

    public:
        IndexBuffer(int max_size);
        virtual ~IndexBuffer();
        virtual unsigned int* generateIndices(int size) = 0;
        void init(unsigned int* indices);
        inline unsigned int getCount() { return count; }
        void bind() const;
        void unbind() const;
    };
} // GL

#endif /* IndexBuffer_H */