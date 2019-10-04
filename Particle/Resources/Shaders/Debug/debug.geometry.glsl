#version 410 core

layout (points) in;
layout (line_strip, max_vertices = 2) out;

in VS_OUT {
    vec4 color;
    vec3 index;
} gs_in[];

out vec4 fColor;

uniform vec3 dimensions;
uniform vec2 resolution;
uniform bool showMagnitude;
uniform samplerBuffer tbo_id0;

#define GD dimensions
#define SIZE resolution

#define X GD.x
#define Y GD.y
#define Z GD.z

#define SIZE_X X * SIZE.x
#define SIZE_Y Y * SIZE.y
#define SIZE_Z Z * SIZE.x

int SampleIndex(float x, float y, float z)
{
    int yp = int(y) * int(Y);
    int zp = int(z) * int(Z);
    return yp + zp + int(x);
}

void main(void)
{
    fColor = gs_in[0].color;

    // Center Vertex
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    // End vertex
    vec3 i = gs_in[0].index;

    vec2 cell = (SIZE * 0.5f) * 0.5f;

    vec4 textureSample = texelFetch(tbo_id0, SampleIndex(i.x, i.y, i.z));
    float mag = showMagnitude ? length(textureSample) : 1.0;
    vec4 n = normalize(textureSample);
    gl_Position = gl_in[0].gl_Position + vec4(
                (n.x * cell.x * mag),
                (n.y * cell.y * mag),
                (n.z * cell.x * mag),
                0.0);
    EmitVertex();

    EndPrimitive();
}


