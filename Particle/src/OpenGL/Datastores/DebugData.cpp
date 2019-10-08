#include "PCHeader.h"
#include "DebugData.h"

namespace GL
{

DebugData::DebugData()
{
}

DebugData::~DebugData()
{
  delete VA;
  delete VB;
}

void DebugData::Add(DebugVertex element)
{
    std::lock_guard<std::mutex> lockGuard(mutex);
	vertices.push_back(element);
}

void DebugData::Add(DebugVertex element0, DebugVertex element1)
{
    std::lock_guard<std::mutex> lockGuard(mutex);
	vertices.push_back(element0);
	vertices.push_back(element1);
}

void DebugData::Init()
{
  VA = new VertexArray();
  VA->Init();

  VB = new VertexBuffer<DebugVertex>(GL_DYNAMIC_DRAW);
  VB->Init(sizeof(DebugVertex) * 10000);
  VA->SetLayout(DebugVertex::GetLayout());

  // TODO: Add Data Method
  auto datapointer = VB->Pointer();
  memcpy(datapointer, vertices.data(), vertices.size() * sizeof(DebugVertex));
  VB->PointerRelease();
}

void DebugData::Bind()
{
  VA->Bind();
  VB->Bind();
}


} // namespace GL
