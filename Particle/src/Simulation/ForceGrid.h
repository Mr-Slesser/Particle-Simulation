#ifndef FORCEGRID_H
#define FORCEGRID_H

#include "../OpenGL/Programs/Program.h"
#include "../OpenGL/Datastores/DebugDatastore.h"

namespace PT
{

class ForceGrid
{
private:
    std::mutex mutex;
    Utils::Perlin *perlin;
    std::vector<glm::vec3> debugVertices;
    int debugVerticesOffset;

    std::vector<glm::vec3> forces; // Layout: X-Dir, Y-Dir, Z-Dir, Strength
    glm::vec2 speed_limit;
    glm::vec4 grid_data;

    int rows;
    int columns;
    float dragCoefficient;
    float gravity;
    int octaves;
    float persistance;

    GL::DebugDatastore *debugData;

public:
    ForceGrid(Utils::Perlin *perlin, int _rows, int _columns, int sizeX, int sizeY, GL::DebugDatastore *_debugData);
    ~ForceGrid();

    void update(double &dt);
    void updateDebugLines();
    void setGridData(GL::Program *program);
    glm::vec2 getSpeed() { return speed_limit; }
    void setSpeed(glm::vec2 speed) { speed_limit = speed; }
    float getDragCoeff() { return dragCoefficient; }
    void setDragCoeff(float dragC) { dragCoefficient = dragC; }
    int getOctaves() { return octaves; }
    void setOctaves(int o) { octaves = o; }
    float getPersistance() { return persistance; }
    void setPersistance(float p) { persistance = p; }
    float getGravity() { return gravity; }
    void setGravity(float g) { gravity = g; }

    inline int index(int row, int column) { return (row * rows) + column; };
    inline int elements() { return forces.size(); }
    inline int size() { return sizeof(glm::vec3) * forces.size(); }
    inline glm::vec4 getGridData() { return grid_data; }
    inline std::vector<glm::vec3> getData() { return forces; }
    inline std::vector<glm::vec3> data() { return forces; }

    inline std::vector<glm::vec3> getDebugData() { return debugVertices; }
};

} // namespace PT

#endif /* FORCEGRID_H */
