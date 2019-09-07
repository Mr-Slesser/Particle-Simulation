#ifndef RENDERER_H
#define RENDERER_H

#include "../Programs/ProgramManager.h"
#include "../../Simulation/ForceGrid.h"
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

    /* -------------------- TEXTURE BUFFER OBJECT ----------------------------- */
    unsigned int texBufferID;
    unsigned int texBufferTextureID;
    std::vector<glm::vec3> texBufferData;
    PT::ForceGrid *forces;
    /* ------------------------------------------------------------------------ */

public:
    Renderer();
    ~Renderer();

    bool init(ProgramManager *_programs, Datastore *_datastore, PT::ForceGrid *_forces);
    void clear();
    void draw(double dt);
    void update(double dt);
    void MVP();
    void addParticle(int num);
};

} // namespace GL

#endif /* RENDERER_H */
