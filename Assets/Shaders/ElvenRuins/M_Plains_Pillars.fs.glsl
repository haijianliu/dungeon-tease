
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
uniform sampler2D metallicMap;

vec3 getNormalFromMap(sampler2D normalMap);

void main() {
	vec3 metallicColor = texture(metallicMap, uv).rgb;
	vec3 albedoColor = texture(albedoMap, uv).rgb;

	// passes
	albedoPass = vec4(pow(mix(albedoColor, 2 * albedoColor, metallicColor.g), vec3(2.2)), 1);
	normalPass = vec4(getNormalFromMap(normalMap), 1);

	// generate mrc pass
	float metallic = mix(0, 1, metallicColor.g);
	float roughness = mix(0.85, 0.98, albedoColor.r);
	roughness = mix(0.3, roughness, 1 - metallicColor.r);
	roughness = mix(0.3, roughness, 1 - metallicColor.g);
	mrcPass = vec4(metallic, roughness, 1, 1);

	positionPass = vec4(position, 1);
}
