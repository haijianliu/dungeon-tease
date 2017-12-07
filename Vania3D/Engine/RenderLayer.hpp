
#ifndef RenderLayer_hpp
#define RenderLayer_hpp

struct MeshRenderData {
	std::vector<GameObject*> gameObjects;
};

class MaterialLayer {
private:
	Material* material;
	std::unordered_map<Mesh*, MeshRenderData*> meshRenderDatas;
	
public:
	MaterialLayer();
	~MaterialLayer();
	
	void add(GameObject* gameObject, unsigned int meshIndex);
	void render(Shader* shader);
};

class ShaderLayer {
private:
	Shader* shader;
	std::unordered_map<Material*, MaterialLayer*> materialLayers;
	std::unordered_map<Material*, MaterialLayer*> materialLayersTwoSides;

public:
	ShaderLayer();
	~ShaderLayer();

	void add(GameObject* gameObject, unsigned int meshIndex);
	void render(GameObject* camera);
};

class RenderLayer {
private:
	std::unordered_map<unsigned int, ShaderLayer*> shaderLayers;

public:
	RenderLayer();
	~RenderLayer();

	void add(GameObject* gameObject);
	void render(GameObject* camera);
};

#endif /* RenderLayer_hpp */
