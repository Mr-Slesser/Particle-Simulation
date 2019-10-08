#version 410 core

in vec3 fragmentPosition;
in vec4 passColour;
in vec3 passNormal;

out vec4 FragColor;

const float AmbientStrength = 0.8;
const float SpecularStrength = 0.5;

uniform vec3 cameraPosition;
uniform vec3 lightPosition;

const float HEIGHT = 200.0f;

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

    vec4 finalColour = passColour;

    if (fragmentPosition.y < 0.3 * HEIGHT) {
        finalColour = vec4(0.98, 0.79, 0.14, 1.0);
    } else if (fragmentPosition.y < 0.4 * HEIGHT) {
        finalColour = vec4(1.0, 0.75, 0.46, 1.0);
    } else if (fragmentPosition.y < 0.7 * HEIGHT) {
        finalColour = vec4(0.42, 0.69, 0.30, 1.0);
    } else if (fragmentPosition.y < 0.9 * HEIGHT) {
        finalColour = vec4(0.34, 0.40, 0.45, 1.0);
    } else {
        finalColour = vec4(1.0, 1.0, 1.0, 1.0);
    }

    FragColor = Lighting * finalColour;
}