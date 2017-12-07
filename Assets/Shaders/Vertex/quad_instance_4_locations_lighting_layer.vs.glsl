
#version 330 core
layout (location = 0) in vec3 positionVertex;
layout (location = 1) in vec2 uvVertex;
layout (location = 2) in vec3 instanceLightColor;
layout (location = 3) in vec3 instanceLightPosition;

out vec2 uv;
out vec3 lightColor;
out vec3 lightPosition;

void main() {
	uv = uvVertex;
	lightColor = instanceLightColor;
	lightPosition = instanceLightPosition;
	gl_Position = vec4(positionVertex, 1.0);
}
