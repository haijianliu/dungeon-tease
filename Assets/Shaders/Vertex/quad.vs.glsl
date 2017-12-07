
#version 330 core
layout (location = 0) in vec3 positionVertex;
layout (location = 1) in vec2 uvVertex;

out vec2 uv;

void main() {
	uv = uvVertex;
	gl_Position = vec4(positionVertex, 1.0);
}
