#include "PCHeader.h"
#include "Simulation.h"

namespace PT
{
Simulation::Simulation(int x, int y, int z, int resolution, int yresolution, GL::Datastore *datastore, GL::DebugDatastore *debugDatastore, GL::ForcesDatastore *forcedatastore)
    : Resolution(glm::vec2(resolution, yresolution)), Dimensions(glm::vec3(x, y, z)), drawDebug(true), datastore(datastore), fds(forcedatastore)
{
//    for (int i = 0; i < 1; i++)
//    {
//        perlins.push_back(new Utils::Perlin((i * 10) * 256));
//    }
//
//    for (int i = 0; i < 1; i++)
//    {
//        forces.push_back(new ForceGrid(perlins[i], glm::vec3(x, y, z), resolution, i * (y * yresolution), debugDatastore));
//    }
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
//            if (this->drawDebug)
//                forces[i]->updateDebugLines();
// 				if (i == 0) forces[0]->updateDebugLines();

        });

        threads.push_back(std::move(thread));
    }

    return threads;
}

void Simulation::PrepareDraw(GL::Program *program)
{
    program->setVec3("dimensions", Dimensions);
    program->setVec2("resolution", Resolution);
    program->setVec2("minMaxSpeed", MinMaxSpeed);
    program->setFloat("dragCoefficient", DragCoefficient);
    program->setFloat("gravity", Gravity);
    program->setInt("samples", Samples);
    program->setFloat("sampleStrength", SampleStrength);
    program->setFloat("sampleStengthDegradation", SampleStengthDegradation);
}

void Simulation::PrepareDebugDraw(GL::Program *program)
{
  	program->setVec3("dimensions", Dimensions);
 	program->setVec2("resolution", Resolution);
 	program->setBool("showMagnitude", Force(0)->isShowingActualMagnitude());
}

void Simulation::AddParticle(int num_to_add)
{
    std::vector<PT::ParticleData> a;

//    auto grid = Force(0)->getDimensions();
//    float X = grid.x * Force(0)->getResolution();
//    float Y = grid.y * Force(0)->getResolution();
//    float Z = grid.z * Force(0)->getResolution();

    auto grid = fds->getDimensions();
    float X = grid.x * fds->getResolution().x;
    float Y = grid.y * fds->getResolution().y;
    float Z = grid.z * fds->getResolution().y;

    for (int i = 0; i < num_to_add; ++i)
    {
        PT::ParticleData v;
        v.position = glm::vec3(Utils::Random::ZeroToOne() * X, 0.0f, Utils::Random::ZeroToOne() * Z);
        v.velocity = glm::vec3(Utils::Random::ZeroToOne(), Utils::Random::ZeroToOne(), Utils::Random::ZeroToOne());
        v.colour = Colour::RED;

        v.lifespan = 1.0f;
        // v.mass = 1.0f;
        v.mass = Utils::Random::RandomRange(0.5f, 1.5f);
        a.push_back(v);
    }

    datastore->submitData(a);
}

} // namespace PT