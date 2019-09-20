#version 410 core
in vec4 outColor;

out vec4 FragColor;

void main()
{
    if (outColor.a <= 0.0)
        discard;

    vec2 temp = gl_PointCoord - vec2(0.5);
    float f = dot(temp, temp);
    if (f > 0.25)
        discard;


    //FragColor = mix(color1, color2, smoothstep(0.1, 0.25, f));
    FragColor = outColor;
}