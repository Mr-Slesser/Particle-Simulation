#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace PT
{
    #define MAX_PARTICLES 1000
    #define PARTICLE_LIFETIME 10.0f

    #define PARTICLE_TYPE_LAUNCHER 0.0f
    #define PARTICLE_TYPE_SHELL 1.0f
    #define PARTICLE_TYPE_SECONDARY_SHELL 2.0f

    #define ZERO_MEM(a) memset(a, 0, sizeof(a))
    #define SAFE_DELETE(p) if (p) { delete p; p = NULL; }
    
    struct Particle
    {
        float Type;    
        glm::vec3 Pos;
        glm::vec3 Vel;    
        float LifetimeMillis;    
    };


    class ParticleSystem
    {
    public:
        ParticleSystem();
        ~ParticleSystem();

            bool InitParticleSystem(const glm::vec& Pos);
    
            void Render(int DeltaTimeMillis, const glm::mat4& VP, const glm::vec3& CameraPos);
    
    private:    
        void UpdateParticles(int DeltaTimeMillis);
        void RenderParticles(const glm::mat4& VP, const glm::vec3& CameraPos);
    
        bool m_isFirst;
        unsigned int m_currVB;
        unsigned int m_currTFB;
        GLuint m_particleBuffer[2];
        GLuint m_transformFeedback[2];
        int m_time;
    };
    
    ParticleSystem::ParticleSystem()
    {
    }
    
    ParticleSystem::~ParticleSystem()
    {
    }
    
} // namespace PT


#endif /* PARTICLESYSTEM_H */
