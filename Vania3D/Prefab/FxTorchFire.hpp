
#ifndef FxTorchFire_hpp
#define FxTorchFire_hpp

class FxTorchFire {
private:
	FxTorchFire();
	
public:
	static FxTorchFire* getInstance();
	~FxTorchFire();
	
	static void createPrefab(std::string name, glm::mat4 model, Scene* scene);
};

#endif /* FxTorchFire_hpp */
