
#ifndef GameObject_hpp
#define GameObject_hpp

class GameObject {
	friend class Scene;

private:
	std::unordered_map<std::type_index, Component*> components;

	void start();
	void update();

public:
	Scene* scene;
	Transform* transform;
	
	bool active = true;
	float lastActiveTime = 0;
	bool staticObject = true;


	GameObject();
	virtual ~GameObject();

	template <typename T> T* addComponent() {
		auto component = new T();
		component->gameObject = this;
		this->components[typeid(T)] = component;
		return component;
	}
	
	template <typename T> void addComponent(T* component) {
		component->gameObject = this;
		this->components[typeid(T)] = component;
	}

	template <typename T> T* getComponent() {
		auto iter = components.find(typeid(T));
		if (iter != std::end(this->components))
			return dynamic_cast<T*>(iter->second);
		return nullptr;
	}
};

#endif /* GameObject_hpp */
