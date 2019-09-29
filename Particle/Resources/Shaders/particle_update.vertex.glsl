#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVelocity;
layout (location = 2) in vec4 inColor;
layout (location = 3) in float inLifespan;
layout (location = 4) in float inMass;

out vec3 outPosition;
out vec3 outVelocity;
out vec4 outColor;
out float outLifespan;
out float outMass;

uniform float dt;
uniform samplerBuffer tbo_id0;

uniform vec2 minMaxSpeed;// x: Min, y: Max
uniform vec2 resolution;
uniform vec3 dimensions;
uniform float dragCoefficient;
uniform float gravity;
uniform int samples;
uniform float sampleStrength;
uniform float sampleStengthDegradation;

#define GD dimensions
#define SL minMaxSpeed
#define SIZE resolution

#define X GD.x
#define Y GD.y
#define Z GD.z

#define SIZE_X X * SIZE.x
#define SIZE_Y Y * SIZE.y
#define SIZE_Z Z * SIZE.x

#define MIN_SPEED SL.x
#define MAX_SPEED SL.y

vec3 CalculateDrag();
vec3 ApplyDrag(vec3 _drag, vec3 _velocity);
vec4 SampleForceTexture();
int SampleIndex(int x, int y, int z);
void CheckBounds();

float map(float value, float min1, float max1, float min2, float max2) {
    return min2 + (value - min1) * (max2 - min2) / (max1 - min1);
}

void main()
{
    if (inLifespan > 0.0)
    {
        vec4 textureSample;

        textureSample = SampleForceTexture();
        vec3 drag = CalculateDrag();
        float gravityModifier = map(inPosition.y, 0.0, (SIZE_Y), 1.0, 5.0); // Want gravity to pull harder the higher it is!

        vec3 calculatedVelocity = vec3(
        clamp(inVelocity.x + (textureSample.x * inMass), MIN_SPEED, MAX_SPEED) * dt,
        clamp(inVelocity.y + (textureSample.y * inMass) - (gravity * gravityModifier * inMass), MIN_SPEED, MAX_SPEED) * dt,
        clamp(inVelocity.z + (textureSample.z * inMass), MIN_SPEED, MAX_SPEED) * dt
        );
        calculatedVelocity = ApplyDrag(drag, calculatedVelocity);

        outPosition = inPosition + calculatedVelocity;
        CheckBounds();

        float r = map(inPosition.y, 0.0, 2 * SIZE_Y, 0.0, 1.0);
        float g = map(calculatedVelocity.x * 20, MIN_SPEED, MAX_SPEED, 0.0, 1.0);
        float b = map(calculatedVelocity.z * 20, MIN_SPEED, MAX_SPEED, 0.0, 1.0);

        outColor = vec4(r, g, b, outLifespan);

        outVelocity = calculatedVelocity;
        outMass = inMass;
    }
    else
    {
        outPosition = inPosition;
        outColor = inColor;
        outLifespan = inLifespan;
        outMass = inMass;
        outVelocity = inVelocity;
    }


}

vec3 CalculateDrag()
{
    float speed = length(inVelocity);
    float dragSpeed = dragCoefficient * speed * speed;
    vec3 drag = inVelocity * -1;
    drag = normalize(drag) * (dragCoefficient * speed * speed) * inMass;
    return vec3(drag.x, drag.y, drag.z);
}

vec3 ApplyDrag(vec3 _drag, vec3 _velocity)
{
    vec3 newVelocity = _velocity;

    if (newVelocity.x >= 0 && newVelocity.x - _drag.x < 0.0) newVelocity.x = 0.0;
    else newVelocity.x -= _drag.x;

    if (newVelocity.y >= 0 && newVelocity.y - _drag.y < 0.0) newVelocity.y = 0.0;
    else newVelocity.y -= _drag.y;

    if (newVelocity.z >= 0 && newVelocity.z - _drag.z < 0.0) newVelocity.z = 0.0;
    else newVelocity.z -= _drag.z;

    return newVelocity;
}

vec4 SampleForceTexture()
{
    vec4 textureSample = vec4(0.0, 0.0, 0.0, 0.0);
    float ss = sampleStrength;

    if (inPosition.y > 0 && inPosition.y <= 2 * SIZE_Y)
    {
        textureSample += (texelFetch(tbo_id0, SampleIndex(0, 0, 0)));

        ss * sampleStengthDegradation;

        for (int i = 1; i <= samples; ++i)
        {
            textureSample += (texelFetch(tbo_id0, SampleIndex(0, 0, i)));   // Top
            textureSample += (texelFetch(tbo_id0, SampleIndex(-i, 0, 0)));  // Left
            textureSample += (texelFetch(tbo_id0, SampleIndex(i, 0, 0)));   // Right
            textureSample += (texelFetch(tbo_id0, SampleIndex(0, 0, -i)));  // Bottom

            ss *= sampleStengthDegradation;
        }
    }

    return textureSample * inMass;
}

int SampleIndex(int x, int y, int z)
{
    int xp = int(int(inPosition.x + x) / SIZE_X);
    int yp = int(int((inPosition.y + y) / SIZE_Y) * Y);
    int zp = int(int((inPosition.z + z) / SIZE_Z) * Z);

    return yp + zp + xp;
}

void CheckBounds()
{
    if (outPosition.y < 0) outPosition.y = 1.0;

    if (outPosition.x > SIZE_X || outPosition.x < 0 ||
    outPosition.z > SIZE_Z || outPosition.z < 0)
    {
        outLifespan = 0.0f;
    }
    else
    {
        outLifespan = inLifespan;
    }
}
