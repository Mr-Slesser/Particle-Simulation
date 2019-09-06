#include "PCHeader.h"
#include "Mathf.h"

namespace Utils
{

float Mathf::Map(float map_this, float from_min, float from_max, float to_min, float to_max)
{
    return (to_max - to_min) * ((map_this - from_min) / (from_max - from_min)) + from_min;
}

float Mathf::Lerp(float v0, float v1, float t)
{
    return (1 - t) * v0 + t * v1;
}

glm::vec3 Mathf::LerpToRandomDirection2D(glm::vec3 input, float strength)
{
    glm::vec2 toValue = glm::circularRand(1.0f);

    return glm::vec3(
        Mathf::Lerp(input.x, toValue.x, strength),
        Mathf::Lerp(input.y, toValue.y, strength),
        input.z);
}
} // namespace Utils
