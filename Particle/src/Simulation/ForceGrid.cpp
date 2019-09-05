#include "PCHeader.h"
#include "ForceGrid.h"

namespace PT
{

ForceGrid::ForceGrid(int _rows, int _columns, int sizeX, int sizeY, GL::DebugData *_debugData)
    : rows(_rows), columns(_columns), debugVerticesOffset(0), debugData(_debugData)
{
    speed_limit = glm::vec2(-1.0f, 1.0f);

    grid_data = glm::vec4(rows, columns, sizeX, sizeY);

    constantForces["drag"] = glm::vec3(0.001f, 0.001f, 0.0f);

    for (int i = 0; i < (rows * columns); ++i)
    {
        // TODO: Limit to size 1 & multiply by a force
        // forces.push_back(glm::vec3((rand() % 5 - 1) / 10.0f, -(rand() % 5 - 1) / 10.0f, 0.0f));
        glm::vec3 vector = glm::vec3(
            ((float)rand() / (RAND_MAX)),
            ((float)rand() / (RAND_MAX)), 0.0f);
        forces.push_back(vector);
    }

} // namespace PT

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
        // forces[i] = glm::vec3(curr.x + ((float)rand() / (RAND_MAX)) * ((float)rand() / (RAND_MAX)), curr.y - ((float)rand() / (RAND_MAX)) * ((float)rand() / (RAND_MAX)), curr.z);

        glm::vec2 random = glm::circularRand(1.0f);

        forces[i] = glm::vec3(
            random.x,
            random.y,
            0.0f);
    }
    // #if _DEBUG_DRAW
    updateDebugLines(1);
    // #endif
}

void ForceGrid::setGridData(GL::Program *program)
{
    program->setVec2("speed_limit", speed_limit);
    program->setVec4("grid_data", grid_data);

    for (const auto &f : constantForces)
    {
        program->setVec3(f.first.c_str(), f.second);
    }
}

void ForceGrid::updateDebugLines(int index)
{
    int sizeX = grid_data.z;
    int sizeY = grid_data.w;

    {
        // debugVertices.clear();
        // for (int y = 0; y < rows - 1; ++y)
        // {
        //     for (int x = 0; x < columns - 1; ++x)
        //     {
        //         // Top
        //         debugVertices.push_back(glm::vec3(x * sizeX, -y * sizeY, 0.0f));
        //         debugVertices.push_back(glm::vec3((x + 1) * sizeX, -y * sizeY, 0.0f));

        //         // Left
        //         debugVertices.push_back(glm::vec3(x * sizeX, -y * sizeY, 0.0f));
        //         debugVertices.push_back(glm::vec3(x * sizeX, -(y + 1) * sizeY, 0.0f));

        //         // Bottom
        //         debugVertices.push_back(glm::vec3(x * sizeX, -(y + 1) * sizeY, 0.0f));
        //         debugVertices.push_back(glm::vec3((x + 1) * sizeX, -(y + 1) * sizeY, 0.0f));

        //         // Right
        //         debugVertices.push_back(glm::vec3((x + 1) * sizeX, -y * sizeY, 0.0f));
        //         debugVertices.push_back(glm::vec3((x + 1) * sizeX, -(y + 1) * sizeY, 0.0f));

        //         debugVerticesOffset += 8;
        //     }
        // }

        //     debugVertices.push_back(glm::vec3(1, 1, 0));
        // }
    }

    float sX = (sizeX * 0.5f) / 2.0f;
    float sY = (sizeY * 0.5f) / 2.0f;

    for (int i = 0; i < rows - 1; ++i)
    {
        for (int j = 0; j < columns - 1; ++j)
        {
            glm::vec3 normalized = glm::normalize(forces[i + j]);

            float x = (j)*sizeX + (sizeX / 2.0f);
            float y = (i)*sizeY + (sizeY / 2.0f);

            debugData->addElement({glm::vec3(x, -y, 0.0f)});
            debugData->addElement({glm::vec3((x + sX / 2.0f) + (normalized.x * sX), (-y + sX / 2.0f) + (normalized.y * sY), 0.0f)});
        }
    }
}
} // namespace PT
