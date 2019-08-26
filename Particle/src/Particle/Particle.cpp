#include "PCHeader.h"
#include "Particle.h"

namespace PT
{
Particle::Particle(Vertex _v)
    : v(_v)
{
}

Particle::~Particle()
{
}

void Particle::setPosition(const glm::vec3 &pos)
{
    v.position = pos;
}

void Particle::setColour(const glm::vec4 &col)
{
    v.colour = col;
}

glm::vec3 &Particle::getPosition()
{
    return v.position;
}

glm::vec4 &Particle::getColour()
{
    return v.colour;
}

} // namespace PT
