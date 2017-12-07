
#version 330 core
layout (location = 0) out vec4 albedoPass;
layout (location = 1) out vec4 normalPass;
layout (location = 2) out vec4 mrcPass;
layout (location = 3) out vec4 positionPass;

in vec3 position;
in vec2 uv;
in vec3 normal;

uniform sampler2D albedoMap0;
uniform sampler2D normalMap0;
uniform sampler2D albedoMap1;
uniform sampler2D normalMap1;
uniform sampler2D mixMap;

vec3 getNormalFromMap(sampler2D normalMap);

void main() {
	// mix color
	float mixColor = 1 - texture(mixMap, uv).r;
	mixColor = smoothstep(0.0, 0.2, mixColor);
	// mix albedo pass
	vec3 albedo0 = pow(texture(albedoMap0, uv).rgb, vec3(2.2));
	vec3 albedo1 = pow(texture(albedoMap1, uv).rgb, vec3(2.2));
	albedoPass = vec4(mix(albedo0, albedo1, mixColor), 1);
	// mix normal pass
	vec3 normal0 = getNormalFromMap(normalMap0);
	vec3 normal1 = getNormalFromMap(normalMap1);
	normalPass = vec4(mix(normal0, normal1, mixColor), 1);
	// generate mrc pass
	// float roughness = mix(0.8, 0.85, albedo1.r);
	// mrcPass = vec4(0, roughness, 1, 1);
	mrcPass = vec4(0, albedo1.r, 1, 1);
	// position and alpha pass
	positionPass = vec4(position, 1);
}

vec3 getNormalFromMap(sampler2D normalMap) {
	vec3 tangentNormal = texture(normalMap, uv).xyz * 2.0 - 1.0;

	vec3 q1 = dFdx(position);
	vec3 q2 = dFdy(position);
	vec2 st1 = dFdx(uv);
	vec2 st2 = dFdy(uv);

	vec3 n = normalize(normal);
	vec3 t = normalize(q1 * st2.t - q2 * st1.t);
	vec3 b = -normalize(cross(n, t));
	mat3 tbn = mat3(t, b, n);

	return normalize(tbn * tangentNormal);
}
