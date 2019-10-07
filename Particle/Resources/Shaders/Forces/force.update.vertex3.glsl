#version 410 core

layout (location = 0) in vec3 inForce;

out vec3 outForce;

uniform samplerBuffer tbo_id0;

uniform float yoffset;
// uniform float xoffset;
// uniform float zoffset;

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
int SampleIndex(vec3 index);

// Some useful functions
vec3 mod289(vec3 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec2 mod289(vec2 x) { return x - floor(x * (1.0 / 289.0)) * 289.0; }
vec3 permute(vec3 x) { return mod289(((x*34.0)+1.0)*x); }
float fbm (vec3 st);
vec3 random3(vec3 c);
float snoise(vec3 p);

void main()
{
    vec3 i = Index3from1(gl_VertexID);
    float xoffset = i.x * 0.01;
    float zoffset = i.z * 0.01;

    float lat = fbm(vec3(0.0, yoffset + i.y, zoffset)) * TWO_PI * 4;
    float lon = fbm(vec3(xoffset, yoffset + i.y, zoffset)) * TWO_PI * 4;

    vec3 force = vec3(
            (0.1 * sin(lon) * cos(lat)),
            (0.01 * sin(lon) * sin(lat)),
            (0.1 * cos(lon))
    );


    // outForce = mix(normalize(inForce), normalize(force), 0.5) * (maxMagnitude * 0.5);
    outForce = normalize(force) * (maxMagnitude * fbm(vec3(xoffset, yoffset + i.y, zoffset)));


}

vec3 Index3from1(int i)
{
    int x = i % int(SIZE.x);
    int y = int(i / int(SIZE.y * SIZE.x));
    int z = int(int(i / SIZE.x) % int(SIZE.y));

    return vec3(x, y, z);
}

int SampleIndex(vec3 index)
{
    int xp = int(int(index.x) / SIZE_X);
    int yp = int(int((index.y) / SIZE_Y) * Y);
    int zp = int(int((index.z) / SIZE_Z) * Z);

    return yp + zp + xp;
}

float fbm (vec3 st) {
    // Initial values
    float value = 0.0;
    float amplitude = .5;
    float frequency = 0.;
    //
    // Loop of octaves
    for (int i = 0; i < octaves; i++) {
        value += amplitude * snoise(st);
        st *= 2.;
        amplitude *= persistence;
    }
    return value;
}

//
// Description : GLSL 2D simplex noise function
//      Author : Ian McEwan, Ashima Arts
//  Maintainer : ijm
//     Lastmod : 20110822 (ijm)
//     License :
//  Copyright (C) 2011 Ashima Arts. All rights reserved.
//  Distributed under the MIT License. See LICENSE file.
//  https://github.com/ashima/webgl-noise
//
const float F3 =  0.3333333;
const float G3 =  0.1666667;
float snoise(vec3 p) {

    vec3 s = floor(p + dot(p, vec3(F3)));
    vec3 x = p - s + dot(s, vec3(G3));

    vec3 e = step(vec3(0.0), x - x.yzx);
    vec3 i1 = e*(1.0 - e.zxy);
    vec3 i2 = 1.0 - e.zxy*(1.0 - e);

    vec3 x1 = x - i1 + G3;
    vec3 x2 = x - i2 + 2.0*G3;
    vec3 x3 = x - 1.0 + 3.0*G3;

    vec4 w, d;

    w.x = dot(x, x);
    w.y = dot(x1, x1);
    w.z = dot(x2, x2);
    w.w = dot(x3, x3);

    w = max(0.6 - w, 0.0);

    d.x = dot(random3(s), x);
    d.y = dot(random3(s + i1), x1);
    d.z = dot(random3(s + i2), x2);
    d.w = dot(random3(s + 1.0), x3);

    w *= w;
    w *= w;
    d *= w;

    return dot(d, vec4(52.0));
}

vec3 random3(vec3 c) {
    float j = 4096.0*sin(dot(c,vec3(17.0, 59.4, 15.0)));
    vec3 r;
    r.z = fract(512.0*j);
    j *= .125;
    r.x = fract(512.0*j);
    j *= .125;
    r.y = fract(512.0*j);
    return r-0.5;
}