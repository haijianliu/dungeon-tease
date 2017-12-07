
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
	albedoPass = vec4(pow(texture(albedoMap, uv).rgb, vec3(2.2)), texture(maskMap, uv).a);
	normalPass = vec4(getNormalFromMap(normalMap), 1);
	mrcPass = vec4(texture(maskMap, uv).b, texture(maskMap, uv).g, texture(maskMap, uv).r, texture(maskMap, uv).a);
	positionPass = vec4(position, 1);
}
