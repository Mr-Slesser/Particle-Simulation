#include "PCHeader.h"
#include "ForceGrid.h"

namespace PT
{

ForceGrid::ForceGrid(Utils::Perlin *perlin, glm::vec3 dimensions, int resolution, int yOffset, GL::DebugDatastore *_debugData)
    : debugData(_debugData)
{
    PROFILE("ForceGrid::ForceGrid");

    data = new ForceGridData(perlin, dimensions, resolution, yOffset);

    for (int y = 0; y < data->Dimensions.y; y++)
    {
        for (int z = 0; z < data->Dimensions.z; z++)
        {
            for (int x = 0; x < data->Dimensions.x; x++)
            {
                forces.push_back(glm::vec3(0.0f, 0.0f, 0.0f));
                debugData->addElement({glm::vec3(x, y, z)});
            }
        }
    }
}

ForceGrid::~ForceGrid()
{
    forces.clear();
    delete data;
}

int ForceGrid::index(int x, int y, int z)
{
    auto dim = data->Dimensions;
    int SY = (int)dim.y;
    int SZ = (int)dim.z;

    return (y * SY) + (z * SZ) + x;
}

void ForceGrid::update(double dt)
{
    PROFILE("ForceGrid::update");

    std::lock_guard<std::mutex> lockGuard(mutex);
    static double yoff = 0.0;
    for (int y = 0; y < data->Dimensions.y; y++)
    {
        double zoff = 0.0;
        for (int z = 0; z < data->Dimensions.z; z++)
        {
            double xoff = 0.0;

            double lat = data->Perlin->Noise(data->Octaves, data->Persistance, xoff, yoff + y, zoff) * TWO_PI * 4;

            for (int x = 0; x < data->Dimensions.x; x++)
            {
                double lon = data->Perlin->Noise(data->Octaves, data->Persistance, xoff, yoff + y, zoff) * TWO_PI * 4;

                float xp = 1.0f * sin(lon) * cos(lat);
                float yp = 0.5f * sin(lon) * sin(lat);
                float zp = 1.0f * cos(lon);

                float mag = sqrt(xp * xp + yp * yp + zp * zp);
                float magnitude = maxMagnitude * data->Perlin->Noise(data->Octaves, data->Persistance, xoff, yoff + y, zoff);
                xp = xp * magnitude / mag;
                yp = yp * magnitude / mag;
                zp = zp * magnitude / mag;

                int i = index(x, y, z);

                forces[i] = glm::vec3(xp, yp, zp);
                xoff += 0.01;
            }
            zoff += 0.01;
        }
        yoff += 0.01 * dt;
    }
}

} // namespace PT
