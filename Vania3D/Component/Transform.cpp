
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Transform::Transform() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Transform::~Transform() {

}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void Transform::update() {
	if (!this->gameObject->staticObject)
        this->updateModel();
}

void Transform::updateModel() {
    this->model = glm::translate(this->position) * glm::scale(this->scale * this->modelScale) * glm::mat4_cast(this->rotation);
}


/*------------------------------------------------------------------------------
< get methods >
------------------------------------------------------------------------------*/
glm::vec3 Transform::front() {
	return glm::normalize(this->rotation * this->game->worldFront);
}

void Transform::setUniform(Shader* shader) {
	shader->setMat4("model", model);
}


/*------------------------------------------------------------------------------
< rotate to desired vec3 by radians >
like slerp, but forbids rotation greater than max angle (in radians)
------------------------------------------------------------------------------*/
void Transform::rotate(glm::vec3 direction, float radians) {
	// no rotation allowed & prevent dividing by 0 later
	// smaller threshold will makes a smoother rotation
	if (radians < 0.001) return;

	// get direction quaternion
	glm::quat directionQuaternion = glm::rotation(this->game->worldFront, direction);

	// update rotation
	float cosTheta = glm::dot(this->rotation, directionQuaternion); // vec dot value is different from quat dot value

	// bigger threshold will makes a more sensitivity rotation
	// when they are already equal, no rotation allowed
	if (cosTheta > 0.9999) return;
	// when they are already opposite, just turn around
	if (cosTheta < -0.9999) {
		this->rotation *= -1.0;
		return;
	}

	// avoid taking the long path around the sphere
	if (cosTheta < 0.0){
		this->rotation *= -1.0;
		cosTheta *= -1.0;
	}

	float deltaTheta = glm::acos(cosTheta);

	// If there is only a 2° difference, and we are allowed 5°,
	if (radians > deltaTheta) {
		this->rotation = directionQuaternion;
	}
	else {
		// This is just like slerp(), but with a custom t
		float factor = radians / deltaTheta;
		this->rotation = glm::slerp(this->rotation, directionQuaternion, factor);
	}
}
