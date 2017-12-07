
#version 330 core
layout (location = 0) out vec4 shadowPass;

in vec2 uv;

uniform sampler2D normalPass;
uniform sampler2D positionPass;

uniform sampler2D shadowMap;
uniform mat4 lightSpaceMatrix;

// shadow
float shadowMapping(mat4 lightSpaceMatrix, vec3 n, vec3 position);

void main() {
	vec3 n = texture(normalPass, uv).rgb;
	vec3 position = texture(positionPass, uv).rgb;
	float shadow = shadowMapping(lightSpaceMatrix, n, position);
	shadowPass = vec4(vec3(shadow), 1);
}
