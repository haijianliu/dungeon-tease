
#version 330 core
layout (location = 0) out vec4 ambientPass;

in vec2 uv;

uniform sampler2D albedoPass;
uniform sampler2D normalPass;
uniform sampler2D mrcPass;
uniform sampler2D positionPass;

// ibl
uniform samplerCube irradianceMap;
uniform samplerCube prefilterMap;
uniform sampler2D brdfLUT;

// transform
uniform vec3 cameraPosition;

const float MAX_REFLECTION_LOD = 4.0;

// brdf
vec3 fresnelSchlickRoughness(float cosTheta, vec3 f0, float roughness) {
	return f0 + (max(vec3(1.0 - roughness), f0) - f0) * pow(1.0 - cosTheta, 5.0);
}

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

	// ibl ambient lighting
	vec3 specularF = fresnelSchlickRoughness(max(dot(n, v), 0.0), f0, roughness);
	vec3 diffuseF = 1.0 - specularF;
	diffuseF *= 1.0 - metallic;
	// ibl diffuse
	vec3 irradiance = texture(irradianceMap, n).rgb;
	vec3 diffuse = irradiance * albedo;
	// ibl specular
	vec3 prefilteredColor = textureLod(prefilterMap, r, roughness * MAX_REFLECTION_LOD).rgb;
	vec2 brdf = texture(brdfLUT, vec2(max(dot(n, v), 0.0), roughness)).rg;
	vec3 specular = prefilteredColor * (specularF * brdf.x + brdf.y);
	// ambient
	// vec3 ambient = diffuseF * diffuse + specularF * diffuse * specular;
	vec3 ambient = specularF * diffuse * specular;

	// fog
	float fog = (80 - length(position - cameraPosition)) / 60;
	fog = clamp(fog, 0, 1);
	ambient = mix(vec3(0.1), ambient, fog);

	ambientPass = vec4(ambient, 1.0);
}
