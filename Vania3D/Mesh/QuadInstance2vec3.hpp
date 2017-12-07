
#ifndef QuadInstance2vec3_hpp
#define QuadInstance2vec3_hpp

struct Instance2vec3 {
	glm::vec3 first, second;
};

class QuadInstance2vec3 {
	friend class RenderPass;
	
private:
	unsigned int vao, vboInstance;
	
public:
	QuadInstance2vec3();
	~QuadInstance2vec3();
	
	void draw(std::vector<Instance2vec3>* instances);
};

#endif /* QuadInstance2vec3_hpp */
