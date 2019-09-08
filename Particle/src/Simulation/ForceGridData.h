#ifndef FORCEGRIDDATA_H
#define FORCEGRIDDATA_H

namespace PT
{

struct ForceGridData
{
    Utils::Perlin *Perlin;
    glm::vec3 Dimensions;
    int Resolution;
    glm::vec2 MinMaxSpeed = glm::vec2(-10.0f, 10.0f);
    float DragCoefficient = 0.6f;
    float Gravity = 0.1f;
    int Octaves = 5;
    float Persistance = 0.6f;
    float SampleStrength = 1.0f;
    float SampleStengthDegradation = 0.5f;
    int Samples = 5;
    int DebugVerticesOffset = 0;

    ForceGridData(Utils::Perlin *perlin, glm::vec3 dimensions, int resolution)
        : Perlin(perlin), Dimensions(dimensions), Resolution(resolution) {}
};

} // namespace PT

#endif /* FORCEGRIDDATA_H */
