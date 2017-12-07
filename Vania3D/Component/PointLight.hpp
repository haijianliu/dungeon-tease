
#ifndef PointLight_hpp
#define PointLight_hpp

class PointLight : public Component {
	friend class FrustumCulling;
	friend class RenderPass;
	
private:
	bool culling = false;

	void start();

public:
	glm::vec3 color = glm::vec3(1);
	float intensity = 1;
	float radius;
	bool distanceCulling = true;

	PointLight();
	~PointLight();
};

#endif /* PointLight_hpp */
