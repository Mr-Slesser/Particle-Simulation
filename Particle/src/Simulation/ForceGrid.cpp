#include "PCHeader.h"
#include "ForceGrid.h"

namespace PT
{

ForceGrid::ForceGrid(Utils::Perlin *perlin, glm::vec3 dimensions, int resolution, int yOffset, GL::DebugDatastore *_debugData)
    : debugData(_debugData)
{
    PROFILE("ForceGrid::ForceGrid");
    data = new ForceGridData(perlin, dimensions, resolution, yOffset);

    int ys = 0, xs = 0, zs = 0;
    for (int y = 0; y < data->Dimensions.y; y++)
    {
        ys++;
        for (int z = 0; z < data->Dimensions.z; z++)
        {
            zs++;
            for (int x = 0; x < data->Dimensions.x; x++)
            {
                xs++;
                forces.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
            }
        }
    }

    std::cout << "X: " << xs << ", Y: " << ys << ", Z: " << zs << std::endl;
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
    int SY = (int)dim.y;
    int SZ = (int)dim.z;

    return (y * SY) + (z * SZ) + x;
}

void ForceGrid::update(double &dt)
{
    PROFILE("ForceGrid::update");

    std::lock_guard<std::mutex> lockGuard(mutex);
    static double yoff = 0.0;
    for (int y = 0; y < data->Dimensions.y - 1; y++)
    {
        double zoff = 0.0;
        for (int z = 0; z < data->Dimensions.z - 1; z++)
        {
            double xoff = 0.0;
            // float lat = Utils::Mathf::Map(z, 0, total, -HALF_PI, HALF_PI);
            double lat = data->Perlin->Noise(data->Octaves, data->Persistance, xoff, zoff, yoff) * TWO_PI * 4;
            for (int x = 0; x < data->Dimensions.x - 1; x++)
            {
                // float lon = Utils::Mathf::Map(x, 0, total, -PI, PI);
                double lon = data->Perlin->Noise(data->Octaves, data->Persistance, xoff, zoff, yoff) * TWO_PI * 4;

                float xp = 1.0f * sin(lon) * cos(lat);
                float yp = 1.0f * sin(lon) * sin(lat);
                float zp = 1.0f * cos(lon);

                int i = index(x, y, z);
                forces[i] = glm::vec3(xp, yp, zp);
                xoff += 0.001;
            }
            zoff += 0.001;
        }
        yoff += 0.001;
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

    float cellSize = (data->Resolution * 0.5f) / 2.0f;
    for (int y = 0; y < data->Dimensions.y; y++)
    {
        for (int z = 0; z < data->Dimensions.z; z++)
        {
            for (int x = 0; x < data->Dimensions.x; x++)
            {
                glm::vec3 n = glm::normalize(forces[y + z + x]);

                float xp = x * data->Resolution + (data->Resolution * 0.5f);
                float yp = y * data->Resolution + (data->Resolution * 0.5f) + data->yOffset;
                float zp = z * data->Resolution + (data->Resolution * 0.5f);

                float dirx = xp + (n.x * cellSize);
                float diry = yp + (n.y * cellSize);
                float dirz = zp + (n.z * cellSize);

                debugData->addElement({glm::vec3(xp, yp, zp)}, {glm::vec3(dirx, diry, dirz)});
            }
        }
    }
}
} // namespace PT
