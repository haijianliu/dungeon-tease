
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
uniform sampler2D factorMap;

vec3 getNormalFromVec3(vec3 n);

void main() {
	float factor = texture(factorMap, uv).g;

	albedoPass = vec4(pow(texture(albedoMap, uv).rgb, vec3(2.2)), 1);

	vec3 normalColor = texture(normalMap, uv).rgb;
	normalColor = mix(normalColor, vec3(0.5, 0.5, 1), factor);
	normalPass = vec4(getNormalFromVec3(normalColor), 1);

	mrcPass = vec4(texture(maskMap, uv).b, texture(maskMap, uv).g, texture(maskMap, uv).r, 1);
	mrcPass = mix(mrcPass, vec4(1, 0, 1, 1), factor);

	positionPass = vec4(position, 1);
}
