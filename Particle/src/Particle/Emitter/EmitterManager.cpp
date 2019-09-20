#include "PCHeader.h"
#include "./EmitterManager.h"

namespace PT
{
EmitterManager::EmitterManager()
{
}

EmitterManager::~EmitterManager()
{
    for (auto e : emitters)
    {
        delete e;
    }
    emitters.clear();
}

void EmitterManager::addEmitter(GL::Datastore *datastore, GUILayer *gui, float intervalMS, glm::vec4 color)
{
    std::stringstream ss;
    ss << "Emitter " << emitters.size();

    emitters.push_back(new Emitter(datastore, gui, ss.str(), color, intervalMS, glm::vec3(100.0f, 0.0f, 100.0f), 1.0f, glm::sphericalRand(1.0f)));
}

void EmitterManager::removeEmitter()
{
    delete emitters.back();
    emitters.pop_back();
}

void EmitterManager::update(GL::DebugDatastore *debugdatastore)
{
    PROFILE("EmitterManager::update");

    for (auto &e : emitters)
    {
        e->update(debugdatastore);
    }
}

} // namespace PT