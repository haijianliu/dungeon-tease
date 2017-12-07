
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

// vec3 getNormalFromVec3(vec3 normal);
vec3 getNormalFromMap(sampler2D normalMap);

void main() {
	vec4 mask = texture(maskMap, uv);

	albedoPass = vec4(pow(texture(albedoMap, uv).rgb, vec3(2.2)), 1);
	normalPass = vec4(getNormalFromMap(normalMap), 1);
	mrcPass = vec4(mask.b, mask.g, mask.r, 1);
	positionPass = vec4(position, 1);
}


// vec3 getNormalFromVec3(vec3 normal);
// vec3 getNormalFromMap(sampler2D normalMap);
//
// void main() {
// 	vec4 mask = texture(maskMap, uv);
// 	vec3 normalColor = vec3(texture(normalMap, uv).rgb);
// 	mask.a > 0 ? mask.a : 0;
// 	normalColor.z += mask.a;
//
// 	albedoPass = vec4(pow(texture(albedoMap, uv).rgb, vec3(2.2)), 1);
// 	normalPass = vec4(getNormalFromVec3(normalColor), 1);
// 	mrcPass = vec4(mask.b, mask.g, mask.r, 1);
// 	positionPass = vec4(position, 1);
// }
