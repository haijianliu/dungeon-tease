
#version 330 core
layout (location = 0) out vec4 albedoPass;
layout (location = 1) out vec4 normalPass;
layout (location = 2) out vec4 mrcPass;
layout (location = 3) out vec4 positionPass;

in vec3 position;
in vec3 normal;

void main() {
	albedoPass = vec4(1);
	normalPass = vec4(normal, 1);
	mrcPass = vec4(0, 1, 1, 1);
	positionPass = vec4(position, 1);
}
