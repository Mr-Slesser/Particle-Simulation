#version 410 core

layout (location = 0) in vec3 inForce;

out vec3 outForce;

uniform samplerBuffer tbo_id0;


uniform float yoffset;
uniform float xoffset;
uniform float zoffset;

uniform float dt;

uniform vec2 resolution;
uniform vec3 dimensions;

uniform int octaves;
uniform float persistence;
uniform float maxMagnitude;

#define GD dimensions
#define SIZE resolution

#define X GD.x
#define Y GD.y
#define Z GD.z

#define SIZE_X X * SIZE.x
#define SIZE_Y Y * SIZE.y
#define SIZE_Z Z * SIZE.x

#define TWO_PI 1.57079632679489661923

vec3 Index3from1(int i);
double Noise(int o, double p, double x, double y, double z);

void main()
{
    vec3 index = Index3from1(gl_VertexID);
    vec3 noise = texelFetch(tbo_id0, gl_VertexID).xyz;

    float angle = float(Noise(octaves, persistence, noise.x, noise.y, noise.z)) * TWO_PI * 4;

    float xp = 1.0f * sin(angle) * cos(angle) * dt;
    float yp = 0.1f * sin(angle) * sin(angle) * dt;
    float zp = 1.0f * cos(angle) * dt;

    float mag = sqrt(xp * xp + yp * yp + zp * zp);
    float magnitude = maxMagnitude * angle;

    outForce = vec3(xp, yp, zp) * magnitude / mag;
}


//void main()
//{
//    vec3 index = Index3from1(gl_VertexID);
//
//    float xoffset = index.x * 0.01;
//    float zoffset = index.z * 0.01;
//    float yos = float(yoffset) + (index.y + 1) * 0.01 * float(dt);
//
//    float noise = float(Noise(octaves, persistence, xoffset, yos + index.y, zoffset));
//
//    float lat = float(Noise(octaves, persistence, xoffset, yos + index.y, zoffset)) * TWO_PI * 4;
//    float lon = float(Noise(octaves, persistence, 0.0, yos + index.y, zoffset)) * TWO_PI * 4;
//
//    float xp = 1.0f * sin(lon) * cos(lat);
//    float yp = 0.1f * sin(lon) * sin(lat);
//    float zp = 1.0f * cos(lon);
//
//    float mag = sqrt(xp * xp + yp * yp + zp * zp);
//    float magnitude = maxMagnitude * noise;
//
//    outForce = vec3(xp, yp, zp) * magnitude / mag;
//}

vec3 Index3from1(int i)
{
    int x = i % int(SIZE.x);
    int y = int(i / int(SIZE.y * SIZE.x));
    int z = int(int(i / SIZE.x) % int(SIZE.y));

    return vec3(x, y, z);
}

double Noise(int o, double p, double x, double y, double z)
{
    double total = 0.0;
    double frequency = 1.0;
    double amplitude = 1.0;
    double maximum = 0.0;

    for (int i = 0; i < octaves; i++)
    {
        total += (x * frequency + y * frequency + z * frequency) * amplitude;
        maximum += amplitude;
        amplitude *= persistence;
        frequency *= 2;
    }

    return total / maximum;
}