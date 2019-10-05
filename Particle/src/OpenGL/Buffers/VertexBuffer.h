#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include "../../Particle/Particle.h"
#include "../Primitives/Vertex.h"

namespace GL
{

template <class T>
struct VBPointer
{
    T *start;
    T *it;
    unsigned int size;
};

template <class T>
class VertexBuffer
{
private:
    unsigned int ID;
    unsigned long size;
    GLenum usage;

public:
    VertexBuffer(GLenum _usage);
    ~VertexBuffer();

    void init(const unsigned long &_size);
  	void init(const unsigned long &_size, std::vector<T> &data);

    void bind();
    void unbind();

    T *getPointer();
    void releasePointer();

    unsigned int getID() const { return ID; }
};

template<class T>
VertexBuffer<T>::VertexBuffer(GLenum _usage)
	: ID(0), size(0), usage(_usage)
{
  GLCheck(glGenBuffers(1, &ID));
}

template<class T>
VertexBuffer<T>::~VertexBuffer()
{
  GLCheck(glDeleteBuffers(1, &ID));
}

template<class T>
void VertexBuffer<T>::init(const unsigned long &_size)
{
  GL_LOG_TRACE("VertexBuffer<T>::init (null): Size: {}", _size);
  size = _size;
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
  GLCheck(glBufferData(GL_ARRAY_BUFFER, size, NULL, usage));
}

template<class T>
void VertexBuffer<T>::init(const unsigned long &_size, std::vector<T> &data)
{
  GL_LOG_TRACE("VertexBuffer<T>::init (data): Size: {}", _size);
  size = _size;
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, ID));
  GLCheck(glBufferData(GL_ARRAY_BUFFER, size, data.data(), usage));
}

template<class T>
void VertexBuffer<T>::bind()
{
  glBindBuffer(GL_ARRAY_BUFFER, ID);
}

template<class T>
void VertexBuffer<T>::unbind()
{
  GLCheck(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

template<class T>
T *VertexBuffer<T>::getPointer()
{
  return (T *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

template<class T>
void VertexBuffer<T>::releasePointer()
{
  GLCheck(glUnmapBuffer(GL_ARRAY_BUFFER));
}

} // namespace GL

#endif /* VERTEXBUFFER_H */
