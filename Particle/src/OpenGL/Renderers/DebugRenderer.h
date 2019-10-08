#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "../Programs/ProgramManager.h"
#include "../../Simulation/Simulation.h"
#include "../Datastores/DebugDatastore.h"

#include "../Buffers/VertexArray.h"
#include "../Buffers/TextureBuffer.h"

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
  	TextureBuffer *textureBuffer;

private:
public:
    DebugRenderer();
    virtual ~DebugRenderer();

    bool init(ProgramManager *_programs, DebugDatastore *_datastore, PT::Simulation *_simulation, TextureBuffer *_tb);
    void draw();
};

} // namespace GL

#endif /* DEBUGRENDERER_H */
