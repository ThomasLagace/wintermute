#version 330 core

uniform vec3 viewPos;
uniform vec3 lightPos;
uniform vec3 lightPos2;
uniform vec3 mcolor;

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

out vec4 color;

void main() {
    vec3 ambient = vec3(0.3) * mcolor;

    float diffuseFactor = max(dot(normal, normalize(lightPos - fragPos)), 0.0);
    float diffuseFactor2 = max(dot(normal, normalize(lightPos2 - fragPos)), 0.0);
    float diffuseStrength = 2.0;
    vec3 diffuse = (diffuseStrength * diffuseFactor * mcolor * vec3(0.5, 0.5, 0.9)) + (diffuseStrength * diffuseFactor2 * mcolor * vec3(0.5, 0.5, 0.9)); 

    float specularFactor = pow(max(dot(normalize(viewPos - fragPos), reflect(-normalize(lightPos - fragPos), normal)), 0.0), 16.0);
    float specularFactor2 = pow(max(dot(normalize(viewPos - fragPos), reflect(-normalize(lightPos2 - fragPos), normal)), 0.0), 16.0);
    float specularStrength = 2.0;
    vec3 specular = (specularStrength * specularFactor * mcolor) + (specularStrength * specularFactor2 * mcolor);
    
    color = vec4(ambient + diffuse + specular, 1.0);
}

//diffuse = diffuseFactor * something 
//* vec3(r, g, b)
