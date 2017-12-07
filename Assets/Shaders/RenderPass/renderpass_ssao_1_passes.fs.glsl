
#version 330 core
layout (location = 0) out vec4 ssaoPass;

in vec2 uv;

uniform sampler2D normalPass;
uniform sampler2D positionPass;

uniform vec3 samples[64];

uniform mat4 projection;
uniform mat4 view;
uniform mat4 normalMatrix;

int kernelSize = 4;
float radius = 0.2;
float bias = 0.001;

void main() {
	vec3 n = texture(normalPass, uv).rgb;
	vec3 position = texture(positionPass, uv).rgb;

	vec3 positionView = vec3(view * vec4(position, 1));
	vec3 normalView = vec3(normalMatrix * vec4(n, 1));

	vec3 tangent = normalize(vec3(1) - normalView * dot(vec3(1), normalView));
	vec3 bitangent = cross(normalView, tangent);
	mat3 tbn = mat3(tangent, bitangent, normalView);

	float occlusion = 0.0;

	for (int i = 0; i < kernelSize; ++i) {
		// get sample position
		vec3 sampleTBN = tbn * samples[i]; // from tangent to view-space
		sampleTBN = positionView + sampleTBN * radius;

		// project sample position (to sample texture) (to get position on screen/texture)
		vec4 offset = vec4(sampleTBN, 1.0);
		offset = projection * offset; // from view to clip-space
		offset.xyz /= offset.w; // perspective divide
		offset.xyz = offset.xyz * 0.5 + 0.5; // transform to range 0.0 - 1.0

		// get sample depth
		float sampleDepth = (view * texture(positionPass, offset.xy)).z; // get depth value of kernel sample

		// range check & accumulate
		float rangeCheck = smoothstep(0.0, 1.0, radius / abs(positionView.z - sampleDepth));
		occlusion += (sampleDepth >= sampleTBN.z + bias ? 1.0 : 0.0) * rangeCheck;
	}

	ssaoPass = vec4(vec3(1.0 - (occlusion / kernelSize)), 1);
}
