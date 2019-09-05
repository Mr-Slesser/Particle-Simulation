#ifndef DEBUGRENDERER_H
#define DEBUGRENDERER_H

#include "../Programs/ProgramManager.h"
#include "../../Simulation/ForceGrid.h"
#include "../../Core/Camera/CameraManager.h"
#include "./DebugData.h"

#include "../VertexArray.h"

namespace GL
{

class DebugRenderer
{
protected:
    PT::ForceGrid *forces;
    ProgramManager *programs;

    VertexBuffer *VB;
    VertexArray *VA;

private:
public:
    DebugRenderer();
    virtual ~DebugRenderer();

    bool init(ProgramManager* _programs, PT::ForceGrid *_forces);
    void draw(DebugData* datastore);
};

} // namespace GL


#endif /* DEBUGRENDERER_H */
