#ifndef EMITTER_H
#define EMITTER_H

#include "../../Primitives/Vertex.h"
#include "../../Utility/Timer.h"

namespace PT
{
class Emitter
{
private:
    std::vector<Vertex> spawned;
    glm::vec3 position;
    float force;
    glm::vec2 direction;

    Utils::Timer timer;

protected:
public:
    Emitter(
        glm::vec4 color,
        float intervalMS,
        glm::vec3 position,
        float force,
        glm::vec2 direction);

    virtual ~Emitter();

    void spawnParticle(glm::vec4 color);
    std::vector<Vertex> update();
};
} // namespace PT

#endif /* EMITTER_H */
