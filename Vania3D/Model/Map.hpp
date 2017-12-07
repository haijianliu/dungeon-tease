
#ifndef Map_hpp
#define Map_hpp

struct ModelProperties {
	glm::mat4 nodeTransformation;
	std::vector<unsigned int> materialIndices;
};

class Map {
private:
	Game* game;
	
	Node<ModelProperties>* modelNode;
	std::vector<Material*> materialMapping;

	// loads a model with supported assimp extensions from file and stores the resulting data
	void load(Scene* scene, const char* path);
	void processNode(aiNode* ainode, Node<ModelProperties>* node, const aiScene* aiscene);
	// create game objects
	void createGameObjects(Scene* scene, const aiScene* aiscene);
	void processNode(Node<ModelProperties>* node, glm::mat4 parentTransformation, Scene* scene, const aiScene* aiscene);

public:
	Map(Scene* scene, const char* path);
	~Map();
};

#endif /* Map_hpp */
