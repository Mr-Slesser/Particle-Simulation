#ifndef PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_RENDERDATA_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_RENDERDATA_H_

#include "../Buffers/VertexArray.h"
#include "../Primitives/Vertex.h"

namespace GL
{

template <class T>
class RenderData
{
 protected:
  unsigned int numElements;
  unsigned int numIndices;

  VertexBuffer<T> *VBO;
  VertexArray *VAO;
  VBPointer<T> *pointer;

  unsigned int IBO;

 public:
  RenderData(T *data, unsigned int numData, unsigned int *indices, unsigned int numIndex)
  	: numElements(numData), numIndices(numIndex)
  {
	// Setup Pointer
	pointer = new VBPointer<T>();
	pointer->start = pointer->it = nullptr;
	pointer->size = 0;

	VAO = new VertexArray();
	VAO->init();

	VBO = new VertexBuffer<T>(GL_DYNAMIC_DRAW);
	VBO->init(sizeof(T) * (sizeof(data) * sizeof(data[0])));
	auto ptr = VBO->getPointer();
	memcpy(ptr, data, sizeof(T) * numElements);
	VBO->releasePointer();
	ptr = nullptr;

	GL::VBOLayout vbl = VBOLayout();
	vbl.push<float>(3, 0); // Position
	vbl.push<float>(4, 1); // Colour
	vbl.push<float>(3, 0); // Normals
	VAO->setVertexLayout(vbl);

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
  }

  virtual ~RenderData()
  {
	delete pointer;
	delete VBO;
	delete VAO;
  }

  virtual void Update()
  {

  }

  virtual void bindRenderArray()
  {
	VAO->bind();
  }

  virtual void bindVertexBuffer()
  {
	VBO->bind();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
  }

  inline int getVerticesCount() { return numElements; }
  inline int getIndicesSize() { return numIndices; }
  inline VertexBuffer<T> *getVertexBuffer() { return VBO; }
  inline unsigned int getVertexBufferID() { return VBO->getID(); }

  inline VertexArray *getVertexArray() { return VAO; }
  inline VBPointer<T> *getPointer() { return pointer; }
  inline unsigned int getPointerSize() { return pointer->size - 1; }
};

}

#endif //PARTICLE_PARTICLE_SRC_OPENGL_DATASTORES_RENDERDATA_H_
