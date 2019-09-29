#include "PCHeader.h"
#include "Vortex.h"

namespace PT
{
Vortex::~Vortex()
{

}
Vortex::Vortex(const glm::ivec3 &position, float speed, int scale)
	: position(position), speed(speed), scale(scale)
{

}
const glm::ivec3 &Vortex::GetPosition() const
{
  return position;
}

void Vortex::SetPosition(const glm::ivec3 &position)
{
  this->position = position;
}

float Vortex::GetSpeed() const
{
  return speed;
}

void Vortex::SetSpeed(float speed)
{
  this->speed = speed;
}

int Vortex::GetScale() const
{
  return scale;
}

void Vortex::SetScale(int scale)
{
  this->scale = scale;
}

}