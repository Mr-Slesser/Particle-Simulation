#ifndef PARTICLE_TEXTUREBUFFER_H
#define PARTICLE_TEXTUREBUFFER_H

#include "../../Simulation/Simulation.h"

class TextureBuffer {
private:
    unsigned int bufferID;
    unsigned int bufferTextureID;
    GLenum textureUnit;
    PT::ForceGrid *force;

public:
    TextureBuffer(GLenum _textureUnit, PT::ForceGrid* _force);
    virtual ~TextureBuffer();

    void bindTexture();
    void loadData();

    glm::vec3* getPointer();
    void releasePointer();
};

#endif //PARTICLE_TEXTUREBUFFER_H
