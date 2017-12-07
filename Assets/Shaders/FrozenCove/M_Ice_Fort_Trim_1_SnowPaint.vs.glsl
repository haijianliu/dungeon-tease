
#version 330 core
layout (location = 0) in vec3 positionVertex;
layout (location = 1) in vec2 uvVertex;
layout (location = 2) in vec3 normalVertex;

out vec3 position;
out vec2 uv;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
	uv = uvVertex;
	position = vec3(model * vec4(positionVertex, 1.0));
	normal = vec3(model * vec4(normalVertex, 0.0));

	gl_Position =  projection * view * model * vec4(positionVertex, 1.0);
}
