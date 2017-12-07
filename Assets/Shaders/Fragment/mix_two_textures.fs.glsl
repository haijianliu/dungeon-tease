
#version 330 core
layout (location = 0) out vec4 fragColor;

in vec2 uv;
uniform sampler2D textureA;
uniform sampler2D textureB;

void main() {
	fragColor = mix(texture(textureA, uv), texture(textureB, uv), 0.5);
}
