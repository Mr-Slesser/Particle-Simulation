#ifndef SIMULATION_H
#define SIMULATION_H

#include "ForceGrid.h"
#include "../OpenGL/Datastores/Datastore.h"

namespace PT
{
class Simulation
{
private:
    glm::vec3 Dimensions;
    glm::vec2 Resolution;
    glm::vec2 MinMaxSpeed = glm::vec2(-10.0f, 10.0f);
    float DragCoefficient = 0.3f;
    float Gravity = 0.1f;
    int Samples = 5;
    float SampleStrength = 1.0f;
    float SampleStengthDegradation = 0.5f;

    bool drawDebug;

    std::vector<Utils::Perlin *> perlins;
    std::vector<ForceGrid *> forces;

    GL::Datastore *datastore;

public:
    Simulation(int x, int y, int z, int resolution, int yresolution, GL::Datastore *datastore, GL::DebugDatastore *debugDatastore);
    ~Simulation();

    std::vector<std::thread> __Update(double dt);

    void PrepareDraw(GL::Program *program);

    void AddParticle(int num_to_add);

public:
    inline void setDimensions(glm::vec3 d) { Dimensions = d; }
    inline glm::vec3 getDimensions() { return Dimensions; }

    inline glm::vec2 getResolution() { return Resolution; }

    inline void setSpeed(glm::vec2 s) { MinMaxSpeed = s; }
    inline glm::vec2 getSpeed() { return MinMaxSpeed; }

    inline void setDragCoeff(float d) { DragCoefficient = d; }
    inline float getDragCoeff() { return DragCoefficient; }

    inline void setGravity(float g) { Gravity = g; }
    inline float getGravity() { return Gravity; }

    inline void setSamples(int s) { Samples = s; }
    inline int getSamples() { return Samples; }

    inline void setSampleStrength(float s) { SampleStrength = s; }
    inline float getSampleStrength() { return SampleStrength; }

    inline void setSampleStengthDegradation(float s) { SampleStengthDegradation = s; }
    inline float getSampleStengthDegradation() { return SampleStengthDegradation; }

    inline bool shouldDrawDebug() { return drawDebug; }
    void setDrawDebug(bool to) { drawDebug = to; }

    inline Utils::Perlin *Perlin(int index)
    {
        if (index < perlins.size())
            return perlins[index];
        else
        {
            std::cout << "NULLPTR: PERLIN" << std::endl;
            return nullptr;
        }
    }

    inline ForceGrid *Force(int index)
    {
        if (index < forces.size())
            return forces[index];
        else
        {
            std::cout << "NULLPTR: FORCE" << std::endl;
            return nullptr;
        }
    }
};

} // namespace PT

#endif /* SIMULATION_H */
