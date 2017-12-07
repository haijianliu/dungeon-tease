
#ifndef Level_hpp
#define Level_hpp

struct ModelInfo {
	glm::mat4 nodeTransformation = glm::mat4(1);
};

class Level {
private:
	Node<ModelInfo>* modelNode;

	// loads a model with supported assimp extensions from file and stores the resulting data
	void load(const char* path);
	void processNode(aiNode* ainode, Node<ModelInfo>* node, const aiScene* aiscene);
	void processNode(Node<ModelInfo>* node, glm::mat4 parentTransformation, Game* game, Scene* scene);

public:
	Level(const char* path);
	~Level();

	void createGameObjects(Scene* scene);
};

#endif /* Level_hpp */
