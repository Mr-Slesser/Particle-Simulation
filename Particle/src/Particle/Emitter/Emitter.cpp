#include "PCHeader.h"
#include "./Emitter.h"

namespace PT
{
Emitter::Emitter(
    glm::vec4 color,
    float intervalMS,
    glm::vec3 position,
    float force,
    glm::vec2 direction)
    : position(position), force(force), direction(direction)
{
    timer.setInterval([this, color]() { this->spawnParticle(color); }, intervalMS);
}

Emitter::~Emitter()
{
    timer.end();
}

void Emitter::spawnParticle(glm::vec4 color)
{
    Vertex v;
    v.position = glm::vec3(rand() % 200 - 100, rand() % 200 - 100, rand() % 20 - 10);
    v.colour = color;
    spawned.push_back(v);
}

std::vector<Vertex> Emitter::update()
{
    std::vector<Vertex> toReturn;

    if (spawned.size() > 0)
    {
        std::copy(spawned.begin(), spawned.end(), std::back_inserter(toReturn));
        spawned.clear();
    }
    return toReturn;
}
} // namespace PT