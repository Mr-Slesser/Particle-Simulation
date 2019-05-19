#ifndef TRIINDEXBUFFER_HPP
#define TRIINDEXBUFFER_HPP

#include "IndexBuffer.h"

namespace GL
{
    class TriIndexBuffer : public IndexBuffer
    {
    private:
        
    public:
        TriIndexBuffer(int max_size) 
            : IndexBuffer(max_size)
        {
            unsigned int* indices = generateIndices(count);
            init(indices);
        }

        ~TriIndexBuffer() {}

        unsigned int* generateIndices(int size) override
        {
            unsigned int* indices = new unsigned int[size];

            unsigned int offset = 0;
            for (unsigned int  i = 0; i < size; i += 3)
            {
                indices[i]     = offset + 0;
                indices[i + 1] = offset + 1;
                indices[i + 2] = offset + 2;

                offset += 3;
            }

            return indices;
        }
    };
    
} // namespace GL


#endif /* TRIINDEXBUFFER_HPP */
