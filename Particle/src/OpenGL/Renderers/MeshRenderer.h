#ifndef MESH_RENDERER_H
#define MESH_RENDERER_H

#include "../Programs/ProgramManager.h"

namespace GL
{
class MeshRenderer
{
 private:
  std::shared_ptr<ProgramManager> programs;

 public:
  MeshRenderer();
  virtual ~MeshRenderer();

  bool Init(std::shared_ptr<ProgramManager> _programs);
//  void draw();
  void Draw(std::shared_ptr<Renderable> r);

//  void draw(Cube &c);
};
}
#endif // MESH_RENDERER_H
