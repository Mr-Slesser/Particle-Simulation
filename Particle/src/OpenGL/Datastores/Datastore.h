#ifndef DATASTORE_H
#define DATASTORE_H

#include "../../Particle/Particle.h"
#include "../Buffers/VertexArray.h"

namespace GL
{
class Datastore
{
private:
    std::vector<PT::ParticleData> elements;
    std::queue<PT::ParticleData> waitingToSpawn;

    VertexBuffer *vb1;
    VertexBuffer *vb2;
    VertexArray *vaR;
    VertexArray *vaU;
    VBPointer *pointer;

public:
    Datastore();
    virtual ~Datastore();

    void Init();
    void Update();

    void addElement(PT::ParticleData element);
    void addToQueue(PT::ParticleData element);

    void submitData(std::vector<PT::ParticleData> &data);
    void copyData(std::vector<PT::ParticleData> &data);

    void submitData(PT::ParticleData &data);
    void copyData(PT::ParticleData &data);

    void swapBuffers();

    void bindUpdateArray();
    void bindRenderArray();
    void bindVertexBuffer();
    void bindSubVertexBuffer();

    void unbindUpdateArray();
    void unbindRenderArray();
    void unbindVertexBuffer();
    void unbindSubVertexBuffer();

    inline std::vector<PT::ParticleData> &getElements() { return elements; }
    inline PT::ParticleData *getData() { return elements.data(); }
    inline VertexBuffer *getVertexBuffer() { return vb1; }

    inline unsigned int getVertexBufferID() { return vb1->getID(); }
    inline unsigned int getSubVertexBufferID() { return vb2->getID(); }

    inline VertexArray *getUpdateArray() { return vaU; }
    inline VertexArray *getRenderArray() { return vaR; }

    inline VBPointer *getPointer() { return pointer; }
    inline unsigned int getPointerSize() { return pointer->size - 1; }
};

} // namespace GL

#endif /* DATASTORE_H */
