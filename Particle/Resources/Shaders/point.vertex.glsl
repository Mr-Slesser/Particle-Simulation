#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 inVelocity;
layout (location = 2) in vec4 inColor;
layout (location = 3) in float inLifespan;
layout (location = 4) in float inMass;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec4 outColor;

void main()
{
	if (inLifespan > 0.0)
	{
		gl_Position = projection * view * model * vec4(inPosition, 1.0);
		gl_PointSize = (1.0 - inMass / 1.0) * 10.0;
		outColor = inColor;
	}
	else
	{
		gl_Position = projection * view * model * vec4(-1000.0, -10000.0, -10000.0, 1.0);
		outColor = inColor;
	}
}