#ifndef EMITTERMANAGER_H
#define EMITTERMANAGER_H

#include "../../OpenGL/Renderer.h"
#include "./Emitter.h"

#define S_TO_MS(x) x * 1000.0f

class Renderer;

namespace PT
{
class EmitterManager
{
private:
    std::vector<Emitter*> emitters;
    std::vector<Vertex> submission;

protected:
public:
    EmitterManager();
    virtual ~EmitterManager();

    void addEmitter(float intervalMS, glm::vec4 color);
    void removeEmitter();

    void update();
    void submit(GL::Renderer* renderer);
};
} // namespace PT#

#endif /* EMITTERMANAGER_H */
