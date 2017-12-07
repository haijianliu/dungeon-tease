
#version 330 core
out vec4 fragColor;
in vec2 texCoord;
const float PI = 3.14159265359;

/*------------------------------------------------------------------------------
< efficient VanDerCorpus calculation >
http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html
------------------------------------------------------------------------------*/
float radicalInverseVdC(uint bits) {
	bits = (bits << 16u) | (bits >> 16u);
	bits = ((bits & 0x55555555u) << 1u) | ((bits & 0xAAAAAAAAu) >> 1u);
	bits = ((bits & 0x33333333u) << 2u) | ((bits & 0xCCCCCCCCu) >> 2u);
	bits = ((bits & 0x0F0F0F0Fu) << 4u) | ((bits & 0xF0F0F0F0u) >> 4u);
	bits = ((bits & 0x00FF00FFu) << 8u) | ((bits & 0xFF00FF00u) >> 8u);
	return float(bits) * 2.3283064365386963e-10; // / 0x100000000
}

vec2 hammersley(uint i, uint n) {
	return vec2(float(i) / float(n), radicalInverseVdC(i));
}

vec3 importanceSampleGGX(vec2 xi, vec3 n, float roughness) {
	float a = roughness * roughness;
	float phi = 2.0 * PI * xi.x;
	float cosTheta = sqrt((1.0 - xi.y) / (1.0 + (a * a - 1.0) * xi.y));
	float sinTheta = sqrt(1.0 - cosTheta * cosTheta);

	// from spherical coordinates to cartesian coordinates - halfway vector
	vec3 h;
	h.x = cos(phi) * sinTheta;
	h.y = sin(phi) * sinTheta;
	h.z = cosTheta;

	// from tangent-space H vector to world-space sample vector
	vec3 up = abs(n.z) < 0.999 ? vec3(0.0, 0.0, 1.0) : vec3(1.0, 0.0, 0.0);
	vec3 tangent = normalize(cross(up, n));
	vec3 bitangent = cross(n, tangent);

	vec3 sampleVec = tangent * h.x + bitangent * h.y + n * h.z;
	return normalize(sampleVec);
}

float geometrySchlickGGX(float nDotV, float roughness) {
	// k direct
	// float a = (roughness + 1.0);
	// float k = (a * a) / 8.0;
	// k IBL
	float a = roughness;
	float k = (a * a) / 2.0;

	float nom   = nDotV;
	float denom = nDotV * (1.0 - k) + k;

	return nom / denom;
}

float geometrySmith(vec3 n, vec3 v, vec3 l, float roughness) {
	float nDotV = max(dot(n, v), 0.0);
	float nDotL = max(dot(n, l), 0.0);
	float ggx2 = geometrySchlickGGX(nDotV, roughness);
	float ggx1 = geometrySchlickGGX(nDotL, roughness);
	return ggx1 * ggx2;
}

vec2 integrateBRDF(float nDotV, float roughness) {
	vec3 v;
	v.x = sqrt(1.0 - nDotV * nDotV);
	v.y = 0.0;
	v.z = nDotV;

	float a = 0.0;
	float b = 0.0;

	vec3 n = vec3(0.0, 0.0, 1.0);

	const uint SAMPLE_COUNT = 1024u;
	for(uint i = 0u; i < SAMPLE_COUNT; ++i) {
		// generates a sample vector that's biased towards the
		// preferred alignment direction (importance sampling).
		vec2 xi = hammersley(i, SAMPLE_COUNT);
		vec3 h = importanceSampleGGX(xi, n, roughness);
		vec3 l = normalize(2.0 * dot(v, h) * h - v);

		float nDotL = max(l.z, 0.0);
		float nDotH = max(h.z, 0.0);
		float vDotH = max(dot(v, h), 0.0);

		if (nDotL > 0.0) {
			float g = geometrySmith(n, v, l, roughness);
			float gvis = (g * vDotH) / (nDotH * nDotV);
			float fc = pow(1.0 - vDotH, 5.0);
			a += (1.0 - fc) * gvis;
			b += fc * gvis;
		}
	}
	a /= float(SAMPLE_COUNT);
	b /= float(SAMPLE_COUNT);
	return vec2(a, b);
}


void main() {
	vec2 integratedBRDF = integrateBRDF(texCoord.x, texCoord.y);
	fragColor = vec4(integratedBRDF.x, integratedBRDF.y, 0, 1);
}
