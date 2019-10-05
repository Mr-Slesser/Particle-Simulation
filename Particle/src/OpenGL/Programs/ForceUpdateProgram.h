#ifndef PARTICLE_PARTICLE_SRC_OPENGL_PROGRAMS_FORCEUPDATEPROGREAM_H_
#define PARTICLE_PARTICLE_SRC_OPENGL_PROGRAMS_FORCEUPDATEPROGREAM_H_

#include "Program.h"

namespace GL
{

class ForceUpdateProgram : public Program
{
 public:
  ForceUpdateProgram();
  virtual ~ForceUpdateProgram();

  virtual bool init(const char *vertexPath, const char *fragmentPath = "") override;
};
}

#endif //PARTICLE_PARTICLE_SRC_OPENGL_PROGRAMS_FORCEUPDATEPROGREAM_H_
