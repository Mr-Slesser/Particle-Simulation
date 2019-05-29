#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "OpenGL.h"
#include "../Primitives/Vertex.h"

namespace GL
{
    struct VBPointer {
        Vertex* start;
        Vertex* it;
        unsigned int size;
    };

    class VertexBuffer
    {
    private:
        unsigned int ID;
        unsigned long size;
        GLenum usage;
        
    public:
        VertexBuffer(GLenum _usage);
        ~VertexBuffer();

        void init(const unsigned long& _size);

        void bind();

        Vertex* getPointer();
        void releasePointer();
    };
    
} // namespace GL


#endif /* VERTEXBUFFER_H */
