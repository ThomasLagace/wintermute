#version 330 core
uniform vec3 viewPos;
uniform vec3 lightpos;
uniform sampler 2D tex;
in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;
out vec4 color;

void main() {
    vec3 res = vec3(0.0);
    vec3 ambient = 0.1 * texture(tex, texCoord);
    vec3 lightDir = normalize(lightPos - fragPos);
    float diffuseFactor = max(dot(normal, lightDir), 0.0);
    float diffuseStrength = 1.0;
    vec3 diffuse = diffuseStrength * diffuseFactor * texture(tex, texCoord);
    //Specular highlights
    float specularFactor = pow(max(dot(normalize(viewPos - fragPos), normalize(-normalize(lightPos - fragPos), normal)), 0.0), 16.0);
    vec3 specularStrength = 1.0;
    vec3 specular = specularStrength * specularFacot * texture(tex, texCoord);
    result = ambient + diffuse + specular;
    color = vec4(result, 1.0);
}
