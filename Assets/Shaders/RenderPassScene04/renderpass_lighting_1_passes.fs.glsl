
#version 330 core
layout (location = 0) out vec4 lightingPass;

in vec2 uv;

uniform sampler2D albedoPass;
uniform sampler2D normalPass;
uniform sampler2D mrcPass;
uniform sampler2D positionPass;

uniform vec3 lightColor[128];
uniform vec3 lightPosition[128];
uniform float lightRadius[128];
uniform int lightSize;

uniform vec3 cameraPosition;

const float PI = 3.14159265359;

vec3 cookTorranceBRDF(vec3 n, vec3 v, vec3 l, float roughness, vec3 f0);

void main() {
	// passes
	vec3 albedo = texture(albedoPass, uv).rgb;
	vec3 n = texture(normalPass, uv).rgb;
	vec3 mrc = texture(mrcPass, uv).rgb;
	vec3 position = texture(positionPass, uv).rgb;
	// mrc mask
	float metallic = mrc.r;
	float roughness = mrc.g;
	// normals
	vec3 v = normalize(cameraPosition - position);
	vec3 r = reflect(-v, n);
	// f0
	vec3 f0 = vec3(0.04);
	f0 = mix(f0, albedo, vec3(metallic));

	vec3 lightingColor = vec3(0);

	// direct light
	for(int i = 0; i < 1; i++) {
		vec3 l = normalize(vec3(58, 63, 14) - position);
		vec3 specular = cookTorranceBRDF(n, v, l, roughness, f0);
		vec3 diffuseF = 1.0 - specular;
		diffuseF *= 1.0 - metallic;
		lightingColor += (diffuseF * albedo / PI + specular) * vec3(1, 1, 1) * 5 * max(dot(n, l), 0.0);
	}

	for (int i = 0; i < lightSize; i++) {
		// light radiance
		float d = length(lightPosition[i] - position);
		if (d < lightRadius[i]) {
			float attenuation = 1.0 / (d * d);
			vec3 radiance = lightColor[i] * attenuation;
			// normals
			vec3 l = normalize(lightPosition[i] - position);
			// Cook-Torrance BRDF
			vec3 specular = cookTorranceBRDF(n, v, l, roughness, f0);
			// outgoing radiance
			vec3 diffuseF = vec3(1.0) - specular;
			diffuseF *= 1.0 - metallic;
			lightingColor += (diffuseF * albedo / PI + specular) * radiance * max(dot(n, l), 0.0);
		}
	}

	lightingPass = vec4(lightingColor, 1);
}
