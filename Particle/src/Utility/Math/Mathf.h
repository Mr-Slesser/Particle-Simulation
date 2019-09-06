#ifndef MATH_H
#define MATH_H

namespace Utils
{

class Mathf
{
private:
    Mathf();

public:
    virtual ~Mathf();

    static float Map(float map_this, float from_min, float from_max, float to_min, float to_max);
    static float Lerp(float v0, float v1, float t);
    static glm::vec3 LerpToRandomDirection2D(glm::vec3 input, float strength);
};

} // namespace Utils

#endif /* MATH_H */
