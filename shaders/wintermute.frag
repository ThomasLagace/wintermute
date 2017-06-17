#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform sampler2D tex;
in vec2 texCoord;
in vec3 Normal;
in vec3 fragPos;
out vec4 color;

void main() {
    vec3 ambient = vec3(0.1) * vec3(texture(tex, texCoord));
    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuseFactor = max(dot(Normal, lightDir), 0.0);
    float diffuseStrength = 1.0;
    vec3 diffuse = diffuseStrength * diffuseFactor * vec3(texture(tex, texCoord));
    //Specular highlights
    float specularFactor = pow(max(dot(normalize(viewPos - fragPos), reflect(-normalize(lightPos - fragPos), Normal)), 0.0), 16.0);
    float specularStrength = 1.0;
    vec3 specular = specularStrength * specularFactor * vec3(texture(tex, texCoord));
    color = vec4(1.0f);//color = vec4(ambient + diffuse + specular, 1.0);
}
