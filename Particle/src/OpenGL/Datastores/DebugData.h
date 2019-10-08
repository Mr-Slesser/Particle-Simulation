#ifndef DEBUGDATASTORE_H
#define DEBUGDATASTORE_H

#include "../Primitives/Vertex.h"
#include "../Buffers/VertexArray.h"
#include "../Buffers/TextureBuffer.h"

namespace GL
{
class DebugData
{
private:
    std::vector<DebugVertex> vertices;
    std::mutex mutex;

	VertexBuffer<DebugVertex> *VB;
	VertexArray *VA;
	TextureBuffer *textureBuffer;

public:
  DebugData();
    ~DebugData();

    void Add(DebugVertex element);
    void Add(DebugVertex element0, DebugVertex element1);
    void Init();
    void Bind();
    inline std::vector<DebugVertex> Vertices() { return vertices; }
    int Size() { return vertices.size(); }
};

} // namespace GL

#endif /* DEBUGDATASTORE_H */
