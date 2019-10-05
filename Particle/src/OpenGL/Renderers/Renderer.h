#ifndef RENDERER_H
#define RENDERER_H

#include "../Programs/ProgramManager.h"
#include "../../Simulation/ForceGrid.h"
#include "../../Simulation/Simulation.h"
#include "../Datastores/Datastore.h"
#include "../../Utility/Profiler.h"
#include "../Buffers/TextureBuffer.h"

//#define ZERO_MEM(a) memset(a, 0, sizeof(a))

namespace GL
{
class Renderer
{
private:
    ProgramManager *programs;
    Datastore *datastore;

    PT::Simulation *simulation;

public:
    Renderer();
    ~Renderer();

    bool init(ProgramManager *_programs, Datastore *_datastore, PT::Simulation *_simulation);
    void clear();
    void draw(double dt);
    void update(double dt);
    void MVP();
};

} // namespace GL

#endif /* RENDERER_H */
