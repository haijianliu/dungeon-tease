
#ifndef Keyframe_hpp
#define Keyframe_hpp

struct VectorKey {
	float time;
	glm::vec3 value;
};

struct QuaternionKey {
	float time;
	glm::quat value;
};

class Keyframe {
public:
	unsigned int currentPositionIndex = 0;
	unsigned int currentRotationIndex = 0;
	unsigned int currentScalingIndex = 0;
	std::vector<VectorKey> positionKeys;
	std::vector<QuaternionKey> rotationKeys;
	std::vector<VectorKey> scalingKeys;

	Keyframe();
	~Keyframe();
};

#endif /* Keyframe_hpp */
