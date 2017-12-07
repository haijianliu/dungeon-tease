
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Camera::Camera() {
	this->field = 45;
	this->ratio = (float)SCREEN_WIDTH / SCREEN_HEIGHT;;
	this->rangeStart = 0.1;
	this->rangeEnd = 1000;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Camera::~Camera() {

}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void Camera::update() {
	Transform* transform = this->gameObject->getComponent<Transform>();

	// calculate the new front right up vectors
	this->front = glm::normalize(this->target->position - transform->position);
	this->right = glm::normalize(glm::cross(this->front, this->game->worldUp));
	this->up = glm::normalize(glm::cross(this->right, this->front));

	// view matrix (camera position (in world space), target position (in world space), camera up direction)
	this->view = glm::lookAt(transform->position, transform->position + this->front, this->up);

	// projection matrix (field of view, ratio, display range : start unit <-> end units)
	this->projection = glm::perspective(glm::radians(this->field), this->ratio, this->rangeStart, this->rangeEnd);
}


/*------------------------------------------------------------------------------
< set uniforms >
------------------------------------------------------------------------------*/
void Camera::setUniforms(Shader* shader) {
	shader->setMat4("projection", this->projection);
	shader->setMat4("view", this->view);
}
