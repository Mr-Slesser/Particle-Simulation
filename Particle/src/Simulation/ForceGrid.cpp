#include "PCHeader.h"
#include "ForceGrid.h"

namespace PT
{

ForceGrid::ForceGrid(int _rows, int _columns)
    : rows(_rows), columns(_columns)
{
    for (int i = 0; i < (rows * columns); ++i)
    {
        // TODO: Limit to size 1 & multiply by a force
        forces.push_back(glm::vec3((rand() % 5 - 1) / 10.0f, -(rand() % 5 - 1) / 10.0f, 0.0f));
        std::cout << forces.back().x << ", " << forces.back().y << std::endl;
    }
}

ForceGrid::~ForceGrid()
{
    forces.clear();
}

void ForceGrid::update()
{
    for (int i = 0; i < (rows * columns); ++i)
    {
        // TODO: Limit to size 1 & multiply by a force
        glm::vec3 curr = forces[i];
        // forces[i] = glm::vec3(curr.x + (rand() % 10) / 100, curr.y + -(rand() % 100) / 100, curr.z);
    }
}

} // namespace PT
