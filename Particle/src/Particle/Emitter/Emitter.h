#ifndef EMITTER_H
#define EMITTER_H

#include "../Particle.h"
#include "../../OpenGL/Primitives/Vertex.h"
#include "../../Utility/Timer.h"
#include "../../Core/GUI/GUILayer.h"
#include "../../OpenGL/Datastores/DebugDatastore.h"
#include "../../OpenGL/Datastores/Datastore.h"

namespace PT
{
class Emitter
{
private:
    GUILayer *gui;
    glm::vec3 position;
    glm::vec4 color;
    float force;
    glm::vec2 direction;
    Utils::Timer timer;

    GL::Datastore *datastore;

protected:
public:
    Emitter(
        GL::Datastore *_datastore,
        GUILayer *gui,
        std::string name,
        glm::vec4 color,
        float intervalMS,
        glm::vec3 position,
        float force,
        glm::vec2 direction);

    virtual ~Emitter();

    void spawnParticle();
    void update(GL::DebugDatastore *debugdatastore);

    void GUIElement(std::string name);
};
} // namespace PT

#endif /* EMITTER_H */
