
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

vec3 getNormalFromMap(sampler2D normalMap);

void main() {
	albedoPass = vec4(pow(texture(albedoMap0, uv).rgb, vec3(2.2)), 1);
	normalPass = vec4(getNormalFromMap(normalMap0), 1);

	// generate mrc pass
	float roughness = mix(0.85, 0.95, albedoPass.r);
	mrcPass = vec4(0, roughness, 1, 1);

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
