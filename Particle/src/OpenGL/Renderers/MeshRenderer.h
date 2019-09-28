#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "../Datastores/MeshDatastore.h"
#include "../../Core/Camera/CameraManager.h"
#include "../../Utility/Profiler.h"
#include "../Buffers/TextureBuffer.h"

namespace GL
{
class MeshRenderer
{
 private:
  ProgramManager *programs;
  MeshDatastore *datastore;

 public:
  MeshRenderer();
  virtual ~MeshRenderer();

  bool init(ProgramManager *_programs, MeshDatastore *_datastore);
  void draw();
};
}
#endif // MESH_RENDERER_H
