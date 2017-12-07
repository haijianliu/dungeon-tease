
#ifndef UnityScene_hpp
#define UnityScene_hpp

struct UnitySceneData {
	// GameObject
	char name[64];
	// Transform
	unsigned int parentID = 0;
	std::vector<unsigned int> childrenIDs;
	glm::quat rotation;
	glm::vec3 position;
	glm::vec3 scale;
};

class UnityScene {
private:
	std::unordered_map<unsigned int, UnitySceneData*> unitySceneDatas;

public:
	UnityScene();
	~UnityScene();

	void load(const char* path);
};

#endif /* UnityScene_hpp */
