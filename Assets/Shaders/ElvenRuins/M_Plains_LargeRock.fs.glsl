
#version 330 core
layout (location = 0) out vec4 albedoPass;
layout (location = 1) out vec4 normalPass;
layout (location = 2) out vec4 mrcPass;
layout (location = 3) out vec4 positionPass;

in vec3 position;
in vec2 uv;
in vec3 normal;

uniform sampler2D albedoMap;
uniform sampler2D normalMap;

vec3 getNormalFromMap(sampler2D normalMap);

void main() {
	vec3 albedoColor = texture(albedoMap, uv).rgb;
	// passes
	albedoPass = vec4(pow(albedoColor, vec3(2.2)), 1);
	normalPass = vec4(getNormalFromMap(normalMap), 1);
	float roughness = mix(0.88, 0.98, albedoColor.r); // generate mrc pass
	mrcPass = vec4(0, roughness, 1, 1);
	positionPass = vec4(position, 1);
}
