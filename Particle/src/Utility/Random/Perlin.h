#ifndef PERLIN_H
#define PERLIN_H

// Adapated from Ken Perlin's 2002 Java implementation of Improved Noise
// https://cs.nyu.edu/~perlin/noise/
// https://mrl.nyu.edu/~perlin/paper445.pdf

namespace Utils
{

#define DEFAULT_PERLIN_SEED 100

class Perlin
{
protected:
private:
    int seed;

    std::vector<int> p;

private:
    void GenerateBaseData();
    double Fade(double t);
    double Lerp(double t, double a, double b);
    double Grad(int hash, double x, double y, double z);

    double Get(double x, double y, double z);

public:
    Perlin(int seed = DEFAULT_PERLIN_SEED);
    virtual ~Perlin();

    double Noise(int octaves, double persistence, double x, double y = 0.0, double z = 0.0);
};

} // namespace Utils

#endif /* PERLIN2D_H */
