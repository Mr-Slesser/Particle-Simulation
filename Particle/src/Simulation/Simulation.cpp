#include "PCHeader.h"
#include "Simulation.h"

namespace PT
{
Simulation::Simulation(int x, int y, int z, int resolution, GL::DebugDatastore *debugDatastore)
    : Resolution(resolution), Dimensions(glm::vec3(x, y, z)), drawDebug(true)
{
    for (int i = 0; i < 2; i++)
    {
        perlins.push_back(new Utils::Perlin((i + 1) * 256));
    }

    for (int i = 0; i < 2; i++)
    {
        forces.push_back(new ForceGrid(perlins[i], glm::vec3(x, y, z), resolution, i * (y * resolution), debugDatastore));
    }
}

Simulation::~Simulation()
{
    for (int i = 0; i < perlins.size(); i++)
    {
        delete perlins[i];
    }

    for (int i = 0; i < forces.size(); i++)
    {
        delete forces[i];
    }
}

std::vector<std::thread> Simulation::__Update(double dt)
{
    std::vector<std::thread> threads;

    for (int i = 0; i < forces.size(); i++)
    {
        std::thread thread([this, i, &dt] {
            forces[i]->update(dt);
            if (this->drawDebug)
                forces[i]->updateDebugLines();
        });

        threads.push_back(std::move(thread));
    }

    return threads;
}

void Simulation::PrepareDraw(GL::Program *program)
{
    program->setVec3("dimensions", Dimensions);
    program->setInt("resolution", Resolution);
    program->setVec2("minMaxSpeed", MinMaxSpeed);
    program->setFloat("dragCoefficient", DragCoefficient);
    program->setFloat("gravity", Gravity);
    program->setInt("samples", Samples);
    program->setFloat("sampleStrength", SampleStrength);
    program->setFloat("sampleStengthDegradation", SampleStengthDegradation);
}

} // namespace PT