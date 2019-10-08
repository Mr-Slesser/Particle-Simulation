#ifndef CONTAINER_H
#define CONTAINER_H

#include "OpenGL/Datastores/DebugData.h"

class Container : public Object
{
 private:

 public:
  Container(float x, float y, float z, float width, float height, float depth);
  virtual ~Container();
};

#endif //CONTAINER_H
