#version 330 core
layout (location = 0) in vec3 pos;

out vec3 sampleDir;
uniform mat4 proj;
uniform mat4 view;

void main() {
	sampleDir = pos;
	gl_Position = proj * view * vec4(pos, 1.0);
}
