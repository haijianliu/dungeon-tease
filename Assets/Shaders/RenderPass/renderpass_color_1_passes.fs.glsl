
#version 330 core
out vec4 fragColor;

in vec2 uv;
uniform sampler2D color;

void main() {
	fragColor = vec4(texture(color, uv).rgb, 1);
}
