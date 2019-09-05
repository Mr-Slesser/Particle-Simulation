#ifndef FORCEGRID_H
#define FORCEGRID_H

#include "../OpenGL/Programs/Program.h"
#include "../OpenGL/Renderers/DebugData.h"

namespace PT
{

class ForceGrid
{
private:
    std::vector<glm::vec3> debugVertices;
    int debugVerticesOffset;

    std::vector<glm::vec3> forces; // Layout: X-Dir, Y-Dir, Z-Dir, Strength
    glm::vec2 speed_limit;
    glm::vec4 grid_data;

    // Constant forces...
    std::map<std::string, glm::vec3> constantForces;

    int rows;
    int columns;

    GL::DebugData *debugData;

public:
    ForceGrid(int _rows, int _columns, int sizeX, int sizeY, GL::DebugData *_debugData);
    ~ForceGrid();

    void update();

    inline int index(int row, int column) { return (row * rows) + column; };
    inline std::vector<glm::vec3> getData() { return forces; }
    inline std::vector<glm::vec3> data() { return forces; }
    inline int elements() { return forces.size(); }
    inline int size() { return sizeof(glm::vec3) * forces.size(); }

    void setGridData(GL::Program *program);
    void updateDebugLines(int index);
    inline std::vector<glm::vec3> getDebugData() { return debugVertices; }
};

} // namespace PT

#endif /* FORCEGRID_H */
