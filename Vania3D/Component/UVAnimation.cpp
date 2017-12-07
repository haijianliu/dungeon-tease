
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
UVAnimation::UVAnimation(float divideX, float divideY, float sampleTime) {
	this->divideX = divideX;
	this->divideY = divideY;
	this->sampleTime = sampleTime;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
UVAnimation::~UVAnimation() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void UVAnimation::start() {
	glm::vec3 animation = glm::vec3(this->divideX, this->divideY, this->sampleTime);
	MeshRenderer* meshRenderer = this->gameObject->getComponent<MeshRenderer>();
	for (unsigned int i = 0; i < meshRenderer->materials.size(); i++) {
		meshRenderer->materials[i]->shader->use();
		meshRenderer->materials[i]->shader->setVec3("animation", animation);
	}
}
