#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "../Programs/ProgramManager.h"
#include "../../Simulation/ForceGrid.h"
#include "../../Core/Camera/CameraManager.h"
#include "../Datastores/DebugDatastore.h"

#include "../Buffers/VertexArray.h"

namespace GL
{

class DebugRenderer
{
protected:
    PT::ForceGrid *forces0;
    PT::ForceGrid *forces1;
    ProgramManager *programs;

    VertexBuffer<PT::ParticleData> *VB;
    VertexArray *VA;

private:
public:
    DebugRenderer();
    virtual ~DebugRenderer();

    bool init(ProgramManager *_programs, PT::ForceGrid *_forces0, PT::ForceGrid *_forces1);
    void draw(DebugDatastore *datastore);
};

} // namespace GL

#endif /* DEBUGRENDERER_H */
