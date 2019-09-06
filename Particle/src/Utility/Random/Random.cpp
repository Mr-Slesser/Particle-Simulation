#include "PCHeader.h"
#include "Random.h"

namespace Utils
{

Random::Random()
{
}

Random::~Random()
{
}

float Random::ZeroToOne()
{
    return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

float Random::ZeroToN(float n)
{
    return static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / n));
}

float Random::RandomRange(float low, float high)
{
    return low + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (high - low)));
}

} // namespace Utils
