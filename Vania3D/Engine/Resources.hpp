
#ifndef Resources_hpp
#define Resources_hpp

class Resources {
private:
	// Resource storage
	std::unordered_map<const char*, Shader*> shaders;
	std::unordered_map<const char*, Texture*> textures;
	std::unordered_map<std::string, Model*> models;
	std::unordered_map<const char*, LightProbe*> lightProbes;
	std::unordered_map<std::string, Material*> materials;

	Resources();

public:
	static Resources* getInstance();
	~Resources();

	void start();

	Quad* quad;
	QuadInstance2vec3* quadinstance2vec3;
	Skybox* skybox;

	// shader
	void loadShader(const char* name, const char* vertexPath, const char* fragmentPath);
	void loadShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* fuctionPath);
	void loadShader(const char* name, const char* vertexPath, const char* fragmentPath, const char* functionPath1, const char* functionPath2);
	Shader* getShader(const char* name);
	// texture
	void loadTexture(const char* name, const char* path);
	Texture* getTexture(const char* name);
	// model
	void loadModel(std::string name, unsigned int attributeType, const char* path);
	Model* getModel(std::string name);
	// light probe
	void loadLightProbe(const char* name, const char* path);
	LightProbe* getLightProbe(const char* name);
	// material
	void createMaterial(std::string name, Shader* shader);
	Material* getMaterial(std::string name);
};

#endif /* Resources_hpp */
