
#version 330 core
layout (location = 0) out vec4 fxPass;

in vec2 uv;

uniform sampler2D albedoMap;

void main() {
	fxPass = vec4(pow(texture(albedoMap, uv).rgb, vec3(2.2)), 1);
}
