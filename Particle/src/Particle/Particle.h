#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Primitives/Vertex.h"

// TODO: Queue --> Add available indicies to queue so easy to add new in it's place.

namespace PT
{
struct ParticleBufferData
{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 colour;
};

class Particle
{
private:
    Vertex v; // Vertex data in memory linked to this

public:
    Particle(Vertex _v);
    ~Particle();

    void setPosition(const glm::vec3 &pos);
    void setColour(const glm::vec4 &col);

    glm::vec3 &getPosition();
    glm::vec4 &getColour();

    Vertex &getVertex() { return v; }
};
} // namespace PT

#endif /* PARTICLE_H */
