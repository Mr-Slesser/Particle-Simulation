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

void EmitterManager::addEmitter(GUILayer *gui, float intervalMS, glm::vec4 color)
{
    std::stringstream ss;
    ss << "Emitter " << emitters.size();

    emitters.push_back(new Emitter(gui, ss.str(), color, intervalMS, glm::vec3(100.0f, -100.0f, 0.0f), 10.0f, glm::vec2(rand(), -rand())));
}

void EmitterManager::removeEmitter()
{
    delete emitters.back();
    emitters.pop_back();
}

void EmitterManager::update()
{
    for (auto &e : emitters)
    {
        auto newElements = e->update();
        if (newElements.size() > 0)
        {
            submission.insert(end(submission), begin(newElements), end(newElements));
        }
    }
}

void EmitterManager::update(GL::DebugData *datastore)
{
    for (auto &e : emitters)
    {
        auto newElements = e->update(datastore);
        if (newElements.size() > 0)
        {
            submission.insert(end(submission), begin(newElements), end(newElements));
        }
    }
}

void EmitterManager::submit(GL::Renderer *renderer)
{
    if (submission.size() > 0)
    {
        renderer->submitData(submission);
        submission.clear();
    }
}
} // namespace PT