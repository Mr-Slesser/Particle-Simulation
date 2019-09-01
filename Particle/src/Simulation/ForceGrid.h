#ifndef FORCEGRID_H
#define FORCEGRID_H

namespace PT
{

class ForceGrid
{
private:
    std::vector<glm::vec3> forces; // Layout: X-Dir, Y-Dir, Z-Dir, Strength
    int rows;
    int columns;

public:
    ForceGrid(int _rows, int _columns);
    ~ForceGrid();

    void update();

    inline int index(int row, int column) { return (row * rows) + column; };
    inline std::vector<glm::vec3> getData() { return forces; }
    inline std::vector<glm::vec3> data() { return forces; }
    inline int elements() { return forces.size(); }
    inline int size() { return sizeof(glm::vec3) * forces.size(); }
};

} // namespace PT

#endif /* FORCEGRID_H */
