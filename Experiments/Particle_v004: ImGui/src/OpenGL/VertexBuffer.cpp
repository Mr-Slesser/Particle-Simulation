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
        GL_LOG_TRACE("VB::init (def): Size: {}", _size);
        size = _size;
        GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
        GL_LOG_TRACE("VB:(def) A");
		GLCheck(glBufferData(GL_ARRAY_BUFFER, size, NULL, usage));
        GL_LOG_TRACE("VB:(def) B");
    }

    void VertexBuffer::init(const unsigned long& _size, VertexData& vd)
    {
        GL_LOG_TRACE("VB::init: Size: {}", _size);
        size = _size;
        GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
        GL_LOG_TRACE("VB:A");
		GLCheck(glBufferData(GL_ARRAY_BUFFER, size, vd.get().data(), usage));
        GL_LOG_TRACE("VB:B");
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
