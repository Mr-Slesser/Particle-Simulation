#include "PCHeader.h"
#include "ForceGrid.h"

namespace PT
{

ForceGrid::ForceGrid(Utils::Perlin *perlin, glm::vec3 dimensions, int resolution, GL::DebugDatastore *_debugData)
    : debugData(_debugData)
{
    PROFILE("ForceGrid::ForceGrid");
    data = new ForceGridData(perlin, dimensions, resolution);

    for (int y = 0; y < data->Dimensions.y; y++)
    {
        for (int z = 0; z < data->Dimensions.z; z++)
        {
            for (int x = 0; x < data->Dimensions.x; x++)
            {
            }
        }
    }

    for (int i = 0; i < (data->Dimensions.x * data->Dimensions.z); ++i)
    {
        double angle = data->Perlin->Noise(data->Octaves, data->Persistance, 0.0, 0.0, 0.0) * TWO_PI * 4;
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
    debugVertices.clear();
    delete data;
}

int ForceGrid::index(int x, int y, int z)
{
    auto dim = data->Dimensions;
    // int SX = (int)dim.x * data->Resolution;
    int SY = (int)dim.y * data->Resolution;
    int SZ = (int)dim.z * data->Resolution;

    return (y * SY) + (z * SZ) + x;
}

void ForceGrid::update(double &dt)
{
    PROFILE("ForceGrid::update");

    std::lock_guard<std::mutex> lockGuard(mutex);
    static float zoff = 0.0f;
    double xoff = 0;
    for (int y = 0; y < data->Dimensions.x; y++)
    {
        double yoff = 0;
        for (int x = 0; x < data->Dimensions.z; x++)
        {
            double angle = data->Perlin->Noise(data->Octaves, data->Persistance, xoff, zoff, yoff) * TWO_PI * 4;
            int index = x + y * data->Dimensions.z;
            float xp = cos(angle) * angle;
            float zp = sin(angle) * angle;
            // float xp = -1.0f;
            // float zp = -1.0f;
            // float yp = Utils::Random::RandomRange(-1.0f, 1.0f);
            float yp = 0.0f;
            forces[index] = glm::vec3(xp, yp, zp);

            xoff += 0.01;
        }
        yoff += 0.01;
    }
    zoff += 0.001;

    for (int y = 0; y < data->Dimensions.y; y++)
    {
        for (int z = 0; z < data->Dimensions.z; z++)
        {
            for (int x = 0; x < data->Dimensions.x; x++)
            {
            }
        }
    }
}

void ForceGrid::setGridData(GL::Program *program)
{
    PROFILE("ForceGrid::setGridData");

    program->setVec2("minMaxSpeed", data->MinMaxSpeed);
    program->setVec3("dimensions", data->Dimensions);
    program->setInt("resolution", data->Resolution);
    program->setFloat("dragCoefficient", data->DragCoefficient);
    program->setFloat("gravity", data->Gravity);
    program->setInt("samples", data->Samples);
    program->setFloat("sampleStrength", data->SampleStrength);
    program->setFloat("sampleStengthDegradation", data->SampleStengthDegradation);
}

void ForceGrid::updateDebugLines()
{
    PROFILE("ForceGrid::updateDebugLines");

    int sizeX = data->Resolution;
    int sizeY = data->Resolution;
    int sizeZ = data->Resolution;
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

    for (int y = 0; y < data->Dimensions.y; y++)
    {
        for (int z = 0; z < data->Dimensions.z; z++)
        {
            for (int x = 0; x < data->Dimensions.x; x++)
            {
            }
        }
    }

    float sX = (sizeX * 0.5f) / 2.0f;
    float sY = (sizeY * 0.5f) / 2.0f;
    float sZ = (sizeZ * 0.5f) / 2.0f;

    for (int i = 0; i < data->Dimensions.x - 1; ++i)
    {
        for (int j = 0; j < data->Dimensions.z - 1; ++j)
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
