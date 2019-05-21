#ifndef QUADINDEXBUFFER_HPP
#define QUADINDEXBUFFER_HPP

#include "IndexBuffer.h"

namespace GL
{
    class QuadIndexBuffer : public IndexBuffer
    {
    private:
        
    public:
        QuadIndexBuffer(int max_size)
            : IndexBuffer(max_size)
        {
            unsigned int* indices = generateIndices(count);
            init(indices);
        }

        ~QuadIndexBuffer() {}

        unsigned int* generateIndices(int size) override
        {
            unsigned int* indices = new unsigned int[size];

            unsigned int offset = 0;
            for (unsigned int  i = 0; i < size; i += 6)
            {
                indices[i]     = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 3;

                indices[i + 3] = offset + 1;
                indices[i + 4] = offset + 2;
                indices[i + 5] = offset + 3;

                offset += 4;
            }

            return indices;
        }
    };
    
} // namespace GL

#endif /* QUADINDEXBUFFER_HPP */
