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
    bool showActualMagnitude = true;
    float maxMagnitude = 1.0f;

    std::mutex mutex;
    ForceGridData *data;
    GL::DebugDatastore *debugData;
    std::vector<glm::vec3> forces; // Layout: X-Dir, Y-Dir, Z-Dir

public:
    ForceGrid(Utils::Perlin *perlin, glm::vec3 dimensions, int resolution, int yOffset, GL::DebugDatastore *_debugData);
    virtual ~ForceGrid();

    virtual void update(double dt);
    int index(int x, int y, int z);

    inline void setOctaves(int o) { data->Octaves = o; }
    inline void setPersistance(float p) { data->Persistance = p; }

    inline std::vector<glm::vec3> getData() { return forces; }
    inline glm::vec3 *getDataPointer() { return forces.data(); }

    inline int getOctaves() { return data->Octaves; }
    inline float getPersistance() { return data->Persistance; }
    inline int getResolution() { return data->Resolution; }
    inline glm::vec3 getDimensions() { return data->Dimensions; }

    bool isShowingActualMagnitude() { return showActualMagnitude; }
    void setShowActualMagnitude(bool to) { showActualMagnitude = to; }

    float getMaxMagnitude() { return maxMagnitude; }
	void setMaxMagnitude(float to ) {  maxMagnitude = to; }

    inline int elements() { return forces.size(); }
    inline int size() { return sizeof(glm::vec3) * forces.size(); }
};

} // namespace PT

#endif /* FORCEGRID_H */
