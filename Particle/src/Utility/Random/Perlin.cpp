#include "PCHeader.h"
#include "Perlin.h"

namespace Utils
{

Perlin::Perlin(int seed)
    : seed(seed)
{
    GenerateBaseData();
}

Perlin::~Perlin()
{
}

void Perlin::GenerateBaseData()
{
    p.resize(256, 0);
    std::iota(p.begin(), p.end(), 0); // Fill with sequentially increasing values.
    std::default_random_engine random(seed);
    std::shuffle(p.begin(), p.end(), random); // Shuffle elements
    p.insert(p.end(), p.begin(), p.end());    // Duplicate current p and append into p
}

double Perlin::Fade(double t)
{
    return t * t * t * (t * (t * 6 - 15) + 10);
}

double Perlin::Lerp(double t, double a, double b)
{
    return a + t * (b - a);
}

double Perlin::Grad(int hash, double x, double y, double z)
{
    int h = hash & 15;        // CONVERT LO 4 BITS OF HASH CODE
    double u = h < 8 ? x : y, // INTO 12 GRADIENT DIRECTIONS.
        v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
}

double Perlin::Get(double x, double y, double z)
{
    int X = (int)std::floor(x) & 255; // FIND UNIT CUBE THAT
    int Y = (int)std::floor(y) & 255; // CONTAINS POINT.
    int Z = (int)std::floor(z) & 255;

    x -= std::floor(x); // FIND RELATIVE X,Y,Z
    y -= std::floor(y); // OF POINT IN CUBE.
    z -= std::floor(z);

    double u = Fade(x); // COMPUTE FADE CURVES
    double v = Fade(y); // FOR EACH OF X,Y,Z.
    double w = Fade(z);

    // HASH COORDINATES OF THE 8 CUBE CORNERS.
    int A = p[X] + Y;
    int AA = p[A] + Z;
    int AB = p[A + 1] + Z;
    int B = p[X + 1] + Y;
    int BA = p[B] + Z;
    int BB = p[B + 1] + Z;

    return Lerp(w, Lerp(v, Lerp(u, Grad(p[AA], x, y, z),        // AND ADD
                                Grad(p[BA], x - 1, y, z)),      // BLENDED
                        Lerp(u, Grad(p[AB], x, y - 1, z),       // RESULTS
                             Grad(p[BB], x - 1, y - 1, z))),    // FROM  8
                Lerp(v, Lerp(u, Grad(p[AA + 1], x, y, z - 1),   // CORNERS
                             Grad(p[BA + 1], x - 1, y, z - 1)), // OF CUBE
                     Lerp(u, Grad(p[AB + 1], x, y - 1, z - 1),
                          Grad(p[BB + 1], x - 1, y - 1, z - 1))));
}

double Perlin::Noise(int octaves, double persistence, double x, double y, double z)
{
    double total = 0.0;
    double frequency = 1.0;
    double amplitude = 1.0;
    double maximum = 0.0;

    for (int i = 0; i < octaves; i++)
    {
        total += Get(x * frequency, y * frequency, z * frequency) * amplitude;
        maximum += amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }

    return total / maximum;
}

} // namespace Utils