
#ifndef OffsetTransform_hpp
#define OffsetTransform_hpp

class Offset : public Component {
private:
	void update();

public:
	// target
	Transform* parent;
	// properties
	glm::vec3 offsetPosition = glm::vec3(0);

	Offset();
	~Offset();
};

#endif /* OffsetTransform_hpp */
