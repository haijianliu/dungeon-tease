
#ifndef Camera_hpp
#define Camera_hpp

class Camera : public Component {
	friend class FrustumCulling;
	friend class CameraController;
	friend class RenderPass;
	
private:
	// camera attributes
	float field, ratio, rangeStart, rangeEnd;
	// uniforms
	glm::mat4 projection, view;

	void update();

public:
	// properties
	Transform* target;
	// camera angles
	glm::vec3 front, up, right;

	Camera();
	~Camera();

	void setUniforms(Shader* shader);
};

#endif /* Camera_hpp */
