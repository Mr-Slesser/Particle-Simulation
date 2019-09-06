#ifndef PARTICLE_H
#define PARTICLE_H

#include "../OpenGL/Primitives/Vertex.h"

namespace PT
{
struct ParticleData
{
    glm::vec3 position;
    glm::vec3 velocity;
    glm::vec4 colour;
    float lifespan;
    float mass;
};

class Particle
{
private:
    ParticleData data;

public:
    Particle(ParticleData data);
    ~Particle();

    void setPosition(glm::vec3 &pos) { data.position = pos; }
    void setVelocity(glm::vec3 &vel) { data.velocity = vel; }
    void setColour(glm::vec4 &col) { data.colour = col; }
    void setLifespan(float lifespan) { data.lifespan = lifespan; }
    void setMass(float mass) { data.mass = mass; }

    glm::vec3 &getPosition() { return data.position; }
    glm::vec3 &getVelocity() { return data.velocity; }
    glm::vec4 &getColour() { return data.colour; }
    float &getLifespan() { return data.lifespan; }
    float &getMass() { return data.mass; }

    ParticleData &getData() { return data; }
};
} // namespace PT

#endif /* PARTICLE_H */
