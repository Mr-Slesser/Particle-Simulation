#version 410 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec4 inColor;
layout (location = 2) in vec3 inNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec3 fragmentPosition;
out vec4 passColour;
out vec3 passNormal;

void main()
{
    vec4 worldPosition = model * vec4(inPosition, 1.0);
    gl_Position = projection * view * worldPosition;
    fragmentPosition = worldPosition.xyz;
    passColour = inColor;
    passNormal = inNormal;
}