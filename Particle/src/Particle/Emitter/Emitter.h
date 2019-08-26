#ifndef EMITTER_H
#define EMITTER_H

#include "../../Primitives/Vertex.h"
#include "../../Utility/Timer.h"
#include "../../Core/GUI/GUILayer.h"

namespace PT
{
class Emitter
{
private:
    GUILayer *gui;
    std::vector<Vertex> spawned;
    glm::vec3 position;
    glm::vec4 color;
    float force;
    glm::vec2 direction;

    Utils::Timer timer;

protected:
public:
    Emitter(
        GUILayer *gui,
        std::string name,
        glm::vec4 color,
        float intervalMS,
        glm::vec3 position,
        float force,
        glm::vec2 direction);

    virtual ~Emitter();

    void spawnParticle();
    std::vector<Vertex> update();
    void GUIElement(std::string name);
};
} // namespace PT

#endif /* EMITTER_H */
