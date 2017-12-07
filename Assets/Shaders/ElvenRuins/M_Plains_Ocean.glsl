
#version 330 core
layout (location = 0) out vec4 albedoPass;
layout (location = 1) out vec4 normalPass;
layout (location = 2) out vec4 mrcPass;
layout (location = 3) out vec4 positionPass;

in vec3 position;
in vec2 uv;
in vec3 normal;

uniform sampler2D albedoMap;
uniform sampler2D albedoMap2;
uniform sampler2D normalMap;
uniform sampler2D normalMap2;
uniform sampler2D normalMap3;
uniform float time;

vec3 getNormalFromMap(sampler2D normalMap);

void main() {
	vec3 albedoColor = texture(albedoMap, uv).rgb;
	vec3 albedoColor2 = texture(albedoMap2, uv).rgb;
	vec3 normalColor = texture(getNormalFromMap(normalMap), uv).rgb;
	vec3 normalColor2 = texture(getNormalFromMap(normalMap2), uv).rgb;
	vec3 normalColor3 = texture(getNormalFromMap(normalMap3), uv).rgb;

	sinTime = sin(time);
	cosTime = cos(time);

	// texture 1 factor
	float timeFactor1 = mix(0.25, 2 ,sinTime);
	float timeFactor2 = mix(1, 2.5 ,sinTime);
	float texture1Factor = pow(albedoColor.r * timeFactor1, 8) * pow(albedoColor.r * timeFactor2, 8);
	mix(1, 3, textureFactor);

	// texture 2 factor
	float timeFactor3 = clamp(sinTime, 2, 7);
	float timeFactor4 = clamp(cosTime, 0.6, 1.75);
	float texture2Factor = pow(albedoColor2.r, timeFactor3) * timeFactor4;

	// normal 1
	vec3 normalByTime = vec3(normalMap.r * texture2Factor, normalMap.g * texture2Factor, normalMap.b) * vec3(2, 2, 1);
	// normal 2
	vec3 normal2ByTime = vec3(normalMap2.r * texture2Factor, normalMap2.g * 0) * vec3(0.15, 0.15, 0);
	// normal 3
	vec3 normal3ByTime = vec3(normalMap3.r * texture2Factor, normalMap3.g * 0) * vec3(0.075, 0.075, 0);




	// passes
	albedoPass = vec4(pow(albedoColor, vec3(2.2)), 1);
	normalPass = vec4(getNormalFromMap(normalMap), 1);
	float roughness = mix(0.3, 0.7, albedoColor.r); // generate mrc pass
	mrcPass = vec4(1, roughness, 1, 1);
	positionPass = vec4(position, 1);
}
