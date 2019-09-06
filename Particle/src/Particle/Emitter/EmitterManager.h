#ifndef EMITTERMANAGER_H
#define EMITTERMANAGER_H

#include "./Emitter.h"

#include "../../Core/GUI/GUILayer.h"
#include "../../OpenGL/Datastores/DebugDatastore.h"
#include "../../OpenGL/Datastores/Datastore.h"

#define S_TO_MS(x) x * 1000.0f

class Renderer;

namespace PT
{
class EmitterManager
{
private:
    std::vector<Emitter *> emitters;

protected:
public:
    EmitterManager();
    virtual ~EmitterManager();

    void addEmitter(GL::Datastore *datastore, GUILayer *gui, float intervalMS, glm::vec4 color);
    void removeEmitter();

    void update(GL::DebugDatastore *debugdatastore);
};
} // namespace PT

#endif /* EMITTERMANAGER_H */
