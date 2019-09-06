#include "PCHeader.h"
#include "ForceGrid.h"

namespace PT
{

ForceGrid::ForceGrid(int _rows, int _columns, int sizeX, int sizeY, GL::DebugDatastore *_debugData)
    : rows(_rows), columns(_columns), debugVerticesOffset(0), debugData(_debugData)
{
    speed_limit = glm::vec2(0.0f, 1.0f);

    grid_data = glm::vec4(rows, columns, sizeX, sizeY);

    constantForces["drag"] = glm::vec3(0.01f, 0.01f, 0.0f);

    for (int i = 0; i < (rows * columns); ++i)
    {
        glm::vec2 dir = glm::circularRand(1.0f);
        glm::vec3 vector = glm::vec3(dir.x, dir.y, 0.0f);
        forces.push_back(vector);
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
        forces[i] = Utils::Mathf::LerpToRandomDirection2D(forces[i], 0.01f);
    }

    updateDebugLines(1);
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

    // debugData->addElement({glm::vec3(0.0f, 0.0f, 0.0f), Colour::GREEN});
    // debugData->addElement({glm::vec3(-10.0f, 10.0f, 0.0f), Colour::GREEN});

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
