
#ifndef SceneManager_hpp
#define SceneManager_hpp

class SceneManager {
private:
	const char* currentScene;
	std::unordered_map<const char*, Scene*> scenes;

public:
	SceneManager();
	~SceneManager();

	void update();

	void addScene(const char* name, Scene* scene);
	void setActiveScene(const char* name);
};

#endif /* SceneManager_hpp */
