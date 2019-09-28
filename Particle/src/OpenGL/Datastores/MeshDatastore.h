#ifndef MESHDATASTORE_H
#define MESHDATASTORE_H

#include "../Buffers/VertexArray.h"
#include "../Primitives/Vertex.h"

namespace GL
{
class MeshDatastore
{
 private:
  std::vector<MVertex> elements;
  std::vector<unsigned int> indices;


  int width;
  int height;
  int resolution;

  VertexBuffer<MVertex> *VBO;
  VertexArray *VAO;
  VBPointer<MVertex> *pointer;

  unsigned int IBO;

  Utils::Perlin *perlin;

 public:
  MeshDatastore(int _width, int _height, int _resolution = 20);
  virtual ~MeshDatastore();

  void Init();
  void Update();
 void bindRenderArray();
 void bindVertexBuffer();

  void unbindRenderArray();
  void unbindVertexBuffer();

  inline std::vector<MVertex> &getElements() { return elements; }
  inline int getVerticesCount() { return elements.size(); }
  inline int getIndicesSize() { return indices.size(); }
  inline MVertex *getData() { return elements.data(); }
  inline VertexBuffer<MVertex> *getVertexBuffer() { return VBO; }
  inline unsigned int getVertexBufferID() { return VBO->getID(); }

  inline VertexArray *getVertexArray() { return VAO; }
  inline VBPointer<MVertex> *getPointer() { return pointer; }
  inline unsigned int getPointerSize() { return pointer->size - 1; }
};

}

#endif /* MESHDATASTORE_H */
