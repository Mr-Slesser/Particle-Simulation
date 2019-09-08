#include "PCHeader.h"
#include "ForceGrid.h"

namespace PT
{

ForceGrid::ForceGrid(Utils::Perlin *perlin, int _rows, int _columns, int sizeX, int sizeY, GL::DebugDatastore *_debugData)
    : perlin(perlin), rows(_rows), columns(_columns), debugVerticesOffset(0), debugData(_debugData), dragCoefficient(0.6), octaves(5), persistance(0.6), gravity(0.1)
{
    PROFILE("ForceGrid::ForceGrid");

    speed_limit = glm::vec2(-10.0f, 10.0f);
    grid_data = glm::vec4(rows, columns, sizeX, sizeY);

    for (int i = 0; i < (rows * columns); ++i)
    {
        double angle = perlin->Noise(octaves, persistance, 0.0, 0.0, 0.0) * TWO_PI * 4;
        float x = 1.0f * cos(angle);
        // float y = 1.0f * sin(angle);
        float y = 0.0f;
        float z = 1.0f * sin(angle);
        glm::vec3 vector = glm::vec3(x, y, z);

        forces.push_back(vector);
    }
}

ForceGrid::~ForceGrid()
{
    forces.clear();
}

void ForceGrid::update(double &dt)
{
    PROFILE("ForceGrid::update");

    std::lock_guard<std::mutex> lockGuard(mutex);
    static float zoff = 0.0f;
    double xoff = 0;
    for (int y = 0; y < rows; y++)
    {
        double yoff = 0;
        for (int x = 0; x < columns; x++)
        {
            double angle = perlin->Noise(octaves, persistance, xoff, zoff, yoff) * TWO_PI * 4;
            int index = x + y * columns;
            float xp = cos(angle) * angle;
            float zp = sin(angle) * angle;
            // float yp = Utils::Random::RandomRange(-1.0f, 1.0f);
            float yp = 0.0f;
            forces[index] = glm::vec3(xp, yp, zp);

            xoff += 0.01;
        }
        yoff += 0.01;
    }
    zoff += 0.001;
}

void ForceGrid::setGridData(GL::Program *program)
{
    PROFILE("ForceGrid::setGridData");

    program->setVec2("speed_limit", speed_limit);
    program->setVec4("grid_data", grid_data);
    program->setFloat("dragCoefficient", dragCoefficient);
    program->setFloat("gravity", gravity);
    program->setInt("samples", samples);
    program->setFloat("sampleStrength", sampleStrength);
    program->setFloat("sampleStengthDegradation", sampleStengthDegradation);
}

void ForceGrid::updateDebugLines()
{
    PROFILE("ForceGrid::updateDebugLines");

    int sizeX = grid_data.z;
    int sizeY = grid_data.w;
    int sizeZ = grid_data.z;
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
    float sZ = (sizeZ * 0.5f) / 2.0f;

    for (int i = 0; i < rows - 1; ++i)
    {
        for (int j = 0; j < columns - 1; ++j)
        {
            glm::vec3 normalized = glm::normalize(forces[i + j]);

            float x = j * sizeX + (sizeX / 2.0f);
            // float y = i * sizeY + (sizeY / 2.0f);
            float y = 0.0f;
            float z = i * sizeZ + (sizeZ / 2.0f);

            debugData->addElement({glm::vec3(x, y, z)});
            debugData->addElement({glm::vec3((x + sX / 2.0f) + (normalized.x * sX), 0.0f, (z + sZ / 2.0f) + (normalized.z * sZ))});
        }
    }
}
} // namespace PT
