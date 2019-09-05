#ifndef RENDERER_H
#define RENDERER_H

#include "Programs/ProgramManager.h"
#include "../Simulation/ForceGrid.h"

#include "VertexArray.h"
#include "VertexData.h"
#include "Texture.h"

#include "../Particle/Particle.h"
#include "../Core/GlobalConfiguration.h"
#include "../Core/Camera/CameraManager.h"
#include "../Utility/Math.h"
#include "../Utility/Profiler.h"

#define ZERO_MEM(a) memset(a, 0, sizeof(a))

namespace GL
{
class Renderer
{
private:
    const int MAX_PARTICLES = 5000;
    const int total = 10;

    ProgramManager *programs;

    VertexBuffer *vb1;
    VertexBuffer *vb2;
    VertexArray *vaR;
    VertexArray *vaU;

    VertexData vd;
    VertexArray *va;

    VBPointer *pointer;

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

    bool init(ProgramManager *_programs, PT::ForceGrid *_forces);
    void clear();
    void draw();
    void update();
    void MVP();
    void addParticle(int num);

    void submitData(std::vector<PT::ParticleData> &data);
};

} // namespace GL

#endif /* RENDERER_H */
