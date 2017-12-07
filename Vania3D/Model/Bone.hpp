
#ifndef Bone_hpp
#define Bone_hpp

class Bone {
public:
	// bone info
	bool haveBone = false;
	unsigned int index;
	glm::mat4 nodeTransformation;
	glm::mat4 offset;

	// animation transform
	glm::mat4 finalTransformation;
	glm::vec3 scaling;
	glm::quat rotation;
	glm::vec3 translation;

	Bone();
	~Bone ();
	// constructor from values
	Bone(unsigned int index, glm::mat4 offset);
};

#endif /* Bone_hpp */
