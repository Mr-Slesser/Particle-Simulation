#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 resolution;
uniform vec3 dimensions;

out VS_OUT {
	vec4 color;
	vec3 index;
} vs_out;

#define GD dimensions
#define SIZE resolution

#define X GD.x
#define Y GD.y
#define Z GD.z

#define SIZE_X X * SIZE.x
#define SIZE_Y Y * SIZE.y
#define SIZE_Z Z * SIZE.x

vec4 ConvertFromGridToWorld();

void main()
{
	vs_out.index = inPosition;
	gl_Position = projection * view * model * ConvertFromGridToWorld();
	vs_out.color = inColor;
}

vec4 ConvertFromGridToWorld()
{
	float xp = inPosition.x * SIZE.x + (SIZE.x * 0.5f);
	float yp = inPosition.y * SIZE.y + (SIZE.y * 0.5f);
	float zp = inPosition.z * SIZE.x + (SIZE.x * 0.5f);

	return vec4(xp, yp, zp, 1.0);
}
