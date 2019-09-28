#ifndef DATASTORE_H
#define DATASTORE_H

#include "../../Particle/Particle.h"
#include "../Buffers/VertexArray.h"
#include <set>

namespace GL
{
class Datastore
{
private:
  	std::mutex mutex;
    std::vector<PT::ParticleData> elements;
    std::queue<PT::ParticleData> waitingToSpawn;
  	std::queue<int> freeIndices;
  	std::set<int> s;

    VertexBuffer<PT::ParticleData> *vb1;
    VertexBuffer<PT::ParticleData> *vb2;
    VertexArray *vaR;
    VertexArray *vaU;
    VBPointer<PT::ParticleData> *pointer;

public:
    Datastore();
    virtual ~Datastore();

    void Init();
    void Update();
    void checkForFreeIndices();

    void addElement(PT::ParticleData element);
    void addToQueue(PT::ParticleData element);

    void submitData(std::vector<PT::ParticleData> &data);
    void copyData(std::vector<PT::ParticleData> &data);

    void submitData(PT::ParticleData &data);
    void copyData(PT::ParticleData data);

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
    inline VertexBuffer<PT::ParticleData> *getVertexBuffer() { return vb1; }

    inline unsigned int getVertexBufferID() { return vb1->getID(); }
    inline unsigned int getSubVertexBufferID() { return vb2->getID(); }

    inline VertexArray *getUpdateArray() { return vaU; }
    inline VertexArray *getRenderArray() { return vaR; }

    inline VBPointer<PT::ParticleData> *getPointer() { return pointer; }
    inline unsigned int getPointerSize() { return pointer->size - 1; }
};

} // namespace GL

#endif /* DATASTORE_H */
