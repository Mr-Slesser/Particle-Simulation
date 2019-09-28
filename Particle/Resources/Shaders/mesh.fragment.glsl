#version 410 core

in vec3 fragmentPosition;
in vec4 passColour;
in vec3 passNormal;

out vec4 FragColor;

const float AmbientStrength = 0.8;
const float SpecularStrength = 0.5;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;

void main()
{
    // AMBIENT
    vec3 Ambient = AmbientStrength * vec3(0.8, 0.8, 0.8);

    // DIFFUSE
    vec3 nnormal = normalize(passNormal);
    vec3 lightDirection = normalize(lightPosition - fragmentPosition);
    float diff = max(dot(nnormal, lightDirection), 0.0);
    vec3 Diffuse = diff *  vec3(0.9, 0.9, 0.9);

    // Specular
    vec3 viewDirection = normalize(cameraPosition - fragmentPosition);
    vec3 reflectDirection = reflect(-lightDirection, nnormal);
    float spec = pow(max(dot(viewDirection, reflectDirection), 0.0), 32);
    vec3 Specular = SpecularStrength * spec * vec3(1.0, 1.0, 1.0);;

    vec4 Lighting = vec4(Ambient + Diffuse + Specular, 1.0f);

    FragColor = Lighting * passColour;
}