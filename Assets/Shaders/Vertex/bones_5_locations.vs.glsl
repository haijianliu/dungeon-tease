
#version 330 core
layout (location = 0) in vec3 positionVertex;
layout (location = 1) in vec2 uvVertex;
layout (location = 2) in vec3 normalVertex;
layout (location = 3) in ivec4 boneID;
layout (location = 4) in vec4 boneWeight;

out vec3 position;
out vec2 uv;
out vec3 normal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform mat4 bones[52];

void main() {
	// bone transform
	mat4 boneTransform = bones[boneID[0]] * boneWeight[0];
	boneTransform += bones[boneID[1]] * boneWeight[1];
	boneTransform += bones[boneID[2]] * boneWeight[2];
	boneTransform += bones[boneID[3]] * boneWeight[3];

	uv = uvVertex;
	position = vec3(model * boneTransform * vec4(positionVertex, 1.0));
	normal = vec3(model * boneTransform * vec4(normalVertex, 0.0));

	// gl_Position =  projection * view * vec4(WorldPos, 1.0);
	gl_Position =  projection * view * model * boneTransform * vec4(positionVertex, 1.0);
}
