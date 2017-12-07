
#ifndef Mesh_hpp
#define Mesh_hpp

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
};

struct VertexBone {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 uv;
	unsigned int boneID[NUM_BONES_PER_VEREX] = {NULL};
	float weight[NUM_BONES_PER_VEREX] = {0.0};
};

struct VertexFx {
	glm::vec3 position;
	glm::vec2 uv;
};

struct InstanceFx {
	glm::mat4 model;
	float animationTime;
};

class Mesh {
	friend class Model;
	friend class FrustumCulling;
	friend class MaterialLayer;
	friend class MeshRenderer;

private:
	unsigned int vao, count, vaoBounding, vboInstance;
	glm::vec3 boundingMax = glm::vec3(0), boundingMin = glm::vec3(0);
	unsigned int attributeType;

	void createDefaultMesh(const aiMesh* aimesh);
	void createInstanceMesh(const aiMesh* aimesh);
	void createBoneMesh(const aiMesh* aimesh, std::vector<glm::mat4>* pose);
	void createFxMesh(const aiMesh* aimesh);

	static void loadIndices(std::vector<unsigned int>* indices, const aiMesh* aimesh);
	static void boneMapping(std::vector<VertexBone>* vertices, std::vector<glm::mat4>* pose, const aiMesh* aimesh);
	static void updateBounding(glm::vec3 vertexPosition, glm::vec3& boundingMax, glm::vec3& boundingMin);
	static unsigned int createBox(glm::vec3 boundingMax, glm::vec3 boundingMin);

public:
	// constructor
	Mesh(const aiMesh* aimesh, std::vector<glm::mat4>* pose, unsigned int attributeType);
	~Mesh();

	void draw();
	void drawBounding();

	template <typename T> void drawInstance(std::vector<T>* instances) {
		glBindBuffer(GL_ARRAY_BUFFER, this->vboInstance);
		glBufferSubData(GL_ARRAY_BUFFER, 0, instances->size() * sizeof(T), instances->data());
		glDrawElementsInstanced(GL_TRIANGLES, this->count, GL_UNSIGNED_INT, 0, instances->size());
	}
};

#endif /* Mesh_hpp */
