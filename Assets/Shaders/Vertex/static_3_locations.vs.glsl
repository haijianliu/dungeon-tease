
#version 330 core
layout (location = 0) in vec3 positionVertex;
layout (location = 1) in vec2 uvVertex;
layout (location = 2) in vec3 normalVertex;
layout (location = 3) in vec4 instanceMatrix0;
layout (location = 4) in vec4 instanceMatrix1;
layout (location = 5) in vec4 instanceMatrix2;
layout (location = 6) in vec4 instanceMatrix3;

out vec3 position;
out vec2 uv;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform bool instance;

void main() {
	mat4 modelSwitch;
	instance ? modelSwitch[0] = instanceMatrix0 : modelSwitch[0] = model[0];
	instance ? modelSwitch[1] = instanceMatrix1 : modelSwitch[1] = model[1];
	instance ? modelSwitch[2] = instanceMatrix2 : modelSwitch[2] = model[2];
	instance ? modelSwitch[3] = instanceMatrix3 : modelSwitch[3] = model[3];

	position = vec3(modelSwitch * vec4(positionVertex, 1.0));
	uv = uvVertex;
	normal = vec3(modelSwitch * vec4(normalVertex, 0.0));

	gl_Position =  projection * view * modelSwitch * vec4(positionVertex, 1.0);
}
