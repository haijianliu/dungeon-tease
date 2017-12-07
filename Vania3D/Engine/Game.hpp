
#ifndef Game_hpp
#define Game_hpp

class Game {
private:
	Game();

public:
	glm::vec3 worldFront = glm::vec3(0.0,0.0,1.0);
	glm::vec3 worldUp = glm::vec3(0.0,1.0,0.0);
	glm::vec3 worldRight = glm::vec3(1.0,0.0,0.0);

	Window* window;
	Resources* resources;
	Input* input;
	SceneManager* sceneManager;
	RenderPass* renderPass;
	ShadowMapping* shadowMapping;
	Time* time;

	static Game* getInstance();
	~Game();

	void start();
	void update();
};

#endif /* Game_hpp */
