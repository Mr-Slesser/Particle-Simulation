#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "../Programs/ProgramManager.h"
#include "../../Simulation/ForceGrid.h"
#include "../../Core/Camera/CameraManager.h"
#include "../Datastores/DebugDatastore.h"
#include "../Datastores/ForcesDatastore.h"

#include "../Buffers/VertexArray.h"

namespace GL
{

class DebugRenderer
{
protected:
    PT::ForceGrid *forces;
  	PT::Simulation *simulation;
    ProgramManager *programs;
  	DebugDatastore *datastore;

    VertexBuffer<PT::ParticleData> *VB;
    VertexArray *VA;
private:
public:
    DebugRenderer();
    virtual ~DebugRenderer();

    bool init(ProgramManager *_programs, DebugDatastore *_datastore, PT::Simulation *_simulation);
    void draw(ForcesDatastore* forces);
};

} // namespace GL

#endif /* DEBUGRENDERER_H */
