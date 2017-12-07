
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
QuadInstance2vec3::QuadInstance2vec3() {
	unsigned int vbo;
	float quadVertices[] = {
		// positions        // texture Coords
		-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
		 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
		 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
	};
	// setup plane VAO
	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	
	glGenBuffers(1, &this->vboInstance);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboInstance);
	glBufferData(GL_ARRAY_BUFFER, MAX_MESH_INSTANCE * 2 * sizeof(glm::vec3), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)0);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (void*)sizeof(glm::vec3));

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	
	glBindVertexArray(0);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
QuadInstance2vec3::~QuadInstance2vec3() {
	glDeleteVertexArrays(1, &this->vao);
}


/*------------------------------------------------------------------------------
< draw >
------------------------------------------------------------------------------*/
void QuadInstance2vec3::draw(std::vector<Instance2vec3>* instances) {
	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vboInstance);
	glBufferSubData(GL_ARRAY_BUFFER, 0, instances->size() * sizeof(Instance2vec3), instances->data());
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, instances->size());
}
