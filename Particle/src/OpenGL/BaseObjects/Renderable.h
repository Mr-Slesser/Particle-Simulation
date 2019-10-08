#ifndef PARTICLE_PARTICLE_SRC_OPENGL_RENDERABLES_RENDERABLE_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_RENDERABLES_RENDERABLE_H_

#include "../Buffers/VertexArray.h"
#include "../Primitives/Vertex.h"

namespace  GL
{
  class Renderable
  {
   protected:
	unsigned int countElements;
	unsigned int countIndices;

	VertexArray *vao;
	VertexBuffer<Vertex> *vbo;
	unsigned int IBO;

   public:
	virtual ~Renderable()
	{
	  delete vao;
	  delete vbo;
	  GLCheck(glDeleteBuffers(1, &IBO));
	}

	virtual void Bind()
	{
	  vao->Bind();
	  vbo->Bind();
	  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
	}

	inline unsigned int Vertices() { return countElements; }
	inline unsigned int Indices() { return countIndices; }

	inline VertexArray *VAO() { return vao; }
	inline VertexBuffer<Vertex> *VBO() { return vbo; }

	inline Vertex *Pointer() { return vbo->Pointer(); }
	inline void PointerRelease() { vbo->PointerRelease(); }

   protected:
	virtual void __Init(std::vector<Vertex> &data, std::vector<unsigned int> &indices)
	{
	  countElements = data.size();
	  countIndices = indices.size();

	  vao = new VertexArray();
	  vao->Init();

	  vbo = new VertexBuffer<Vertex>(GL_DYNAMIC_DRAW);
	  vbo->Init(sizeof(Vertex) * countElements);

	  // TODO: Init with data!!
	  auto ptr = Pointer();
	  memcpy(ptr, data.data(), sizeof(Vertex) * countElements);
	  PointerRelease();
	  ptr = nullptr;

	  vao->SetLayout(Vertex::GetLayout());

	  GLCheck(glGenBuffers(1, &IBO));
	  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
	  GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, countIndices * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW));
	}

	virtual void __ChangeData(std::vector<Vertex> &data, std::vector<unsigned int> &indices)
	{
	  countElements = data.size();
	  countIndices = indices.size();

	  vbo->Bind();
	  GLCheck(glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * countElements, data.data(), GL_DYNAMIC_DRAW));

	  GLCheck(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO));
	  GLCheck(glBufferData(GL_ELEMENT_ARRAY_BUFFER, countIndices * sizeof(unsigned int), indices.data(), GL_DYNAMIC_DRAW));
	}
  };
}

#endif //PARTICLE_PARTICLE_SRC_OPENGL_RENDERABLES_RENDERABLE_H_
