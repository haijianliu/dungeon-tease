
// normal distribution function (NDF), GGX/Trowbridge-Reitz
float normalDistributionGGX(vec3 n, vec3 h, float roughness) {
	float a = roughness * roughness;
	float a2 = a * a;
	float ndoth = max(dot(n, h), 0.0);
	float ndoth2 = ndoth * ndoth;

	float nominator = a2;
	float denominator = (ndoth2 * (a2 - 1.0) + 1.0);
	denominator = PI * denominator * denominator;

	return nominator / denominator;
}

float geometrySchlickGGX(float ndotv, float roughness) {
	// k direct
	float a = (roughness + 1.0);
	float k = (a * a) / 8.0;
	// k IBL
	// float a = roughness;
	// float k = (a * a) / 2.0;

	float nominator = ndotv;
	float denominator = ndotv * (1.0 - k) + k;

	return nominator / denominator;
}

// specular geometric attenuation, Schlick model
float geometrySmith(vec3 n, vec3 v, vec3 l, float roughness) {
	float ndotv = max(dot(n, v), 0.0);
	float ndotl = max(dot(n, l), 0.0);
	float ggx1 = geometrySchlickGGX(ndotv, roughness);
	float ggx2 = geometrySchlickGGX(ndotl, roughness);

	return ggx1 * ggx2;
}


// Schlick’s approximation, Spherical Gaussian approximation
vec3 fresnelSchlick(float cosTheta, vec3 f0) {
	return f0 + (1.0 - f0) * pow(1.0 - cosTheta, 5.0);
}

// Cook-Torrance BRDF
vec3 cookTorranceBRDF(vec3 n, vec3 v, vec3 l, float roughness, vec3 f0) {
	vec3 h = normalize(v + l);
	float specularD = normalDistributionGGX(n, h, roughness);
	float specularG = geometrySmith(n, v, l, roughness);
	vec3 specularF = fresnelSchlick(max(dot(h, v), 0.0), f0);
	vec3 nominator = specularD * specularG * specularF;
	float denominator = 4 * max(dot(n, v), 0.0) * max(dot(n, l), 0.0) + 0.001; // 0.001 to prevent divide by zero.
	vec3 specular = nominator / denominator;
	return specular;
}
