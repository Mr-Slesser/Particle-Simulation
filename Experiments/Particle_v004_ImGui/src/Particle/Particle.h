#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Primitives/Vertex.h"

namespace PT
{
    class Particle
    {
    private:
        Vertex v; // Vertex data in memory linked to this
        
    public:
        Particle(Vertex _v);
        ~Particle();

        void setPosition(const glm::vec3& pos);
        void setColour(const glm::vec4& col);

        glm::vec3& getPosition();
        glm::vec4& getColour();

        Vertex& getVertex() { return v; }
    };
} // namespace PT


#endif /* PARTICLE_H */