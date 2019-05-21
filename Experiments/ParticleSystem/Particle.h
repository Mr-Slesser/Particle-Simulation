#ifndef PARTICLE_H
#define PARTICLE_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PT
{
    #define PARTICLE_TYPE_LAUNCHER 0.0f
    #define PARTICLE_TYPE_SHELL 1.0f
    #define PARTICLE_TYPE_SECONDARY_SHELL 2.0f

    struct Particle
    {
        float Type;    
        glm::vec3 Pos;
        glm::vec3 Vel;    
        float LifetimeMillis;   
    };
    
} // namespace PT

#endif /* PARTICLE_H */
