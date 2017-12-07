
#ifndef Model_hpp
#define Model_hpp

enum MESH_ATTRIBUTE_TYPE {
	MESH_ATTRIBUTE_DEFAULT, MESH_ATTRIBUTE_BONE, MESH_ATTRIBUTE_INSTANCE, MESH_ATTRIBUTE_INSTANCE_FX
};

class Model {
	friend class FrustumCulling;
	friend class MaterialLayer;
	friend class MeshRenderer;

private:
	Node<Bone>* boneNode;
	std::vector<Mesh*> meshes;
	std::vector<Animation*> animations;
	std::vector<glm::mat4> pose;
	unsigned int attributeType;
	unsigned int currentAnimation = 0;

	void load(const char* path);
	void processNode(aiNode* ainode, Node<Bone>* node, const aiScene* aiscene);
	
public:
	std::vector<std::string> materialNames;
	bool distanceCulling = false;

	Model();
	Model(unsigned int attributeType, const char* path);
	~Model();

	void addAnimation(Animation* animation);
	void updatePose(unsigned int animationIndex, float timeInSeconds);
	void setPoseUniform(Shader* shader);

	void draw();
	void drawBounding();
};

#endif /* Model_hpp */
