#ifndef FORCEGRID_H
#define FORCEGRID_H

#include "./ForceGridData.h"
#include "../OpenGL/Programs/Program.h"
#include "../OpenGL/Datastores/DebugDatastore.h"

namespace PT
{

class ForceGrid
{
private:
    std::mutex mutex;
    ForceGridData *data;
    GL::DebugDatastore *debugData;
    std::vector<glm::vec3> debugVertices;
    std::vector<glm::vec3> forces; // Layout: X-Dir, Y-Dir, Z-Dir, Strength

public:
    ForceGrid(Utils::Perlin *perlin, glm::vec3 dimensions, int resolution, int yOffset, GL::DebugDatastore *_debugData);
    virtual ~ForceGrid();

    virtual void update(double &dt);
    virtual void updateDebugLines();
    int index(int x, int y, int z);

    void setGridData(GL::Program *program);

    inline void setSpeed(glm::vec2 s) { data->MinMaxSpeed = s; }
    inline void setDragCoeff(float d) { data->DragCoefficient = d; }
    inline void setOctaves(int o) { data->Octaves = o; }
    inline void setPersistance(float p) { data->Persistance = p; }
    inline void setGravity(float g) { data->Gravity = g; }
    inline void setDimensions(glm::vec3 d) { data->Dimensions = d; }
    inline void setSampleStrength(float s) { data->SampleStrength = s; }
    inline void setSampleStengthDegradation(float s) { data->SampleStengthDegradation = s; }
    inline void setSamples(int s) { data->Samples = s; }

    inline std::vector<glm::vec3> getData() { return forces; }
    inline glm::vec3 *getDataPointer() { return forces.data(); }
    inline std::vector<glm::vec3> getDebugData() { return debugVertices; }

    inline glm::vec2 getSpeed() { return data->MinMaxSpeed; }
    inline float getDragCoeff() { return data->DragCoefficient; }
    inline int getOctaves() { return data->Octaves; }
    inline float getPersistance() { return data->Persistance; }
    inline float getGravity() { return data->Gravity; }
    inline glm::vec3 getDimensions() { return data->Dimensions; }
    inline int getResolution() { return data->Resolution; }
    inline float getSampleStrength() { return data->SampleStrength; }
    inline float getSampleStengthDegradation() { return data->SampleStengthDegradation; }
    inline int getSamples() { return data->Samples; }

    inline int elements() { return forces.size(); }
    inline int size() { return sizeof(glm::vec3) * forces.size(); }
};

} // namespace PT

#endif /* FORCEGRID_H */
