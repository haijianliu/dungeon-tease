
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
uniform sampler2D maskMap;

vec3 getNormalFromMap(sampler2D normalMap);

void main() {
	vec4 albedo = texture(albedoMap, uv);
	if (albedo.a < 0.5) discard;

	vec4 mask = texture(maskMap, uv);

	albedoPass = vec4(pow(albedo.rgb, vec3(2.2)), 1);
	normalPass = vec4(getNormalFromMap(normalMap), 1);
	mrcPass = vec4(0, mask.r, mask.g, 1);
	positionPass = vec4(position, 1);
}
