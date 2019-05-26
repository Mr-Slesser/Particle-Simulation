#include "VertexBuffer.h"

namespace GL
{
    VertexBuffer::VertexBuffer(GLenum _usage)
        : ID(0), size(0), usage(_usage)
    {
        GLCheck(glGenBuffers(1, &ID));
    }
    
    VertexBuffer::~VertexBuffer()
    {
        GLCheck(glDeleteBuffers(1, &ID));
    }

    void VertexBuffer::init(const unsigned long& _size)
    {
        size = _size;
        GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
		GLCheck(glBufferData(GL_ARRAY_BUFFER, size, NULL, usage));
    }

    void VertexBuffer::bind()
    {
        GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
    }

    Vertex* VertexBuffer::getPointer()
    {
        return (Vertex*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
    }

    void VertexBuffer::releasePointer()
	{
		GLCheck(glUnmapBuffer(GL_ARRAY_BUFFER));
	}

} // namespace GL
