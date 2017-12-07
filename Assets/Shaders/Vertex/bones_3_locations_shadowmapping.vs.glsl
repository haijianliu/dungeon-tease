
#version 330 core
layout (location = 0) in vec3 positionVertex;
layout (location = 3) in ivec4 boneID;
layout (location = 4) in vec4 boneWeight;

uniform mat4 lightSpaceMatrix;
uniform mat4 model;

uniform mat4 bones[52];

void main() {
	// bone transform
	mat4 boneTransform = bones[boneID[0]] * boneWeight[0];
	boneTransform += bones[boneID[1]] * boneWeight[1];
	boneTransform += bones[boneID[2]] * boneWeight[2];
	boneTransform += bones[boneID[3]] * boneWeight[3];

	gl_Position =  lightSpaceMatrix * model * boneTransform * vec4(positionVertex, 1.0);
}
