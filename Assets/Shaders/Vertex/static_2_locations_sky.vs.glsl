
#version 330 core
layout (location = 0) in vec3 positionVertex;
layout (location = 1) in vec2 uvVertex;

out vec2 uv;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	uv = uvVertex;
	gl_Position =  projection * view * model * vec4(positionVertex, 1.0);
}
