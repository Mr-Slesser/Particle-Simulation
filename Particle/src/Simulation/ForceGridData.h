#ifndef FORCEGRIDDATA_H
#define FORCEGRIDDATA_H

namespace PT
{

struct ForceGridData
{
    Utils::Perlin *Perlin;
    glm::vec3 Dimensions;
    int Resolution;
    int Octaves = 5;
    int yOffset;
    float Persistance = 0.6f;
    int DebugVerticesOffset = 0;

    ForceGridData(Utils::Perlin *perlin, glm::vec3 dimensions, int resolution, int yOffset)
        : Perlin(perlin), Dimensions(dimensions), Resolution(resolution), yOffset(yOffset) {}
};

} // namespace PT

#endif /* FORCEGRIDDATA_H */
