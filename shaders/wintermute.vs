#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;
out vec3 fragPos;
out vec3 normal;
out vec2 texCoord;
uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main() {
    gl_Poisition = proj * view * model * vec4(pos, 1.0);
    fragPos = vec3(model * vec4(pos, 1.0));
    normal = normalize(mat3(transpose(inverse(model))) * normal);
}
