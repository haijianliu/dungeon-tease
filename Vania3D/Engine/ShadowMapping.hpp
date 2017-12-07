
#ifndef ShadowMapping_hpp
#define ShadowMapping_hpp

class ShadowMapping {
	friend class Game;
	friend class RenderPass;
	friend class Scene;
	friend class MeshRenderer;

private:
	Game* game;
	unsigned int fbo, depthMap;

	// uniforms
	glm::mat4 projection, view, lightSpace;

	void render(std::vector<MeshRenderer*>* shadowQueue);

public:
	// shadow mapping properties
	Shader* shader;
	int size;
	GameObject* target;
	glm::vec3 lightPositionOffset;
	float range, nearPlane, farPlane;

	void start();

	ShadowMapping();
	~ShadowMapping();
};

#endif /* ShadowMapping_hpp */
