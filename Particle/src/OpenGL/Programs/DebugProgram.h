#ifndef DEBUGPROGRAM_H
#define DEBUGPROGRAM_H

#include "Program.h"

namespace GL
{
class DebugProgram : public Program
{
 public:
  DebugProgram();
  virtual ~DebugProgram() {};

  virtual bool init(const char *vertexPath = PATH("Shaders/point.vertex.glsl"), const char *fragmentPath = PATH("Shaders/point.fragment.glsl")) override;

};

} // namespace GL

#endif /* DEBUGPROGRAM_H */
