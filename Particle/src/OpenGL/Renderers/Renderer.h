#ifndef RENDERER_H
#define RENDERER_H

#include "../Programs/ProgramManager.h"
#include "../../Simulation/ForceGrid.h"
#include "../../Simulation/Simulation.h"
#include "../Datastores/Datastore.h"

#include "../../Core/GlobalConfiguration.h"
#include "../../Core/Camera/CameraManager.h"
#include "../../Utility/Profiler.h"

#define ZERO_MEM(a) memset(a, 0, sizeof(a))

namespace GL
{
class Renderer
{
private:
    ProgramManager *programs;
    Datastore *datastore;

    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;

    PT::Simulation *simulation;

    /* -------------------- TEXTURE BUFFER OBJECT 0----------------------------- */
    // PT::ForceGrid *forces0;

    unsigned int texBufferID0;
    unsigned int texBufferTextureID0;
    /* ------------------------------------------------------------------------ */

    /* -------------------- TEXTURE BUFFER OBJECT 1----------------------------- */
    // PT::ForceGrid *forces1;

    unsigned int texBufferID1;
    unsigned int texBufferTextureID1;
    /* ------------------------------------------------------------------------ */

public:
    Renderer();
    ~Renderer();

    bool init(ProgramManager *_programs, Datastore *_datastore, PT::Simulation *_simulation);
    void clear();
    void draw(double dt);
    void update(double dt);
    void MVP();
    void addParticle(int num);
};

} // namespace GL

#endif /* RENDERER_H */
