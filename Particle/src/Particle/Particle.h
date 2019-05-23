#ifndef PARTICLE_H
#define PARTICLE_H

#include "../Primitives/Vertex.h"

namespace PT
{
    class Particle
    {
    private:
        Vertex vertex;
        
    public:
        Particle();
        ~Particle();
    };
} // namespace PT


#endif /* PARTICLE_H */
