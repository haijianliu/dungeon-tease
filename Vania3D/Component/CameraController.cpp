
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
CameraController::CameraController() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
CameraController::~CameraController() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void CameraController::start() {
	Camera* camera = this->camera->getComponent<Camera>();
	Transform* transform = this->camera->getComponent<Transform>();
	this->offsetFromTarget = transform->position - camera->target->position;
}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void CameraController::update() {
	// input
	glm::vec3 axisRS = this->game->input->getAxisRS();
	this->rotate(this->inverseHorizonal * this->rotateSensitivityHorizonal * axisRS.x * this->game->time->deltaTime, this->inverseVertical * this->rotateSensitivityVertical * axisRS.z * this->game->time->deltaTime);
	if (this->game->input->getJoystickPress(JOY_L2))
		this->zoom(this->game->time->deltaTime * this->zoomSensitivity);
	if (this->game->input->getJoystickPress(JOY_R2))
		this->zoom(-this->game->time->deltaTime * this->zoomSensitivity);

	if (this->game->input->getJoystickTrigger(JOY_UP))
		this->camera->getComponent<Camera>()->field = 90;
	if (this->game->input->getJoystickTrigger(JOY_DOWN))
		this->camera->getComponent<Camera>()->field = 45;

	// update camera transform position
	Camera* camera = this->camera->getComponent<Camera>();
	Transform* transform = this->camera->getComponent<Transform>();
	transform->position = camera->target->position + this->offsetFromTarget;
}


/*------------------------------------------------------------------------------
< rotate >
------------------------------------------------------------------------------*/
void CameraController::rotate(float radiansHorizonal, float radiansVertical) {
	Camera* camera = this->camera->getComponent<Camera>();

	// horizonal
	glm::quat rotationHorizonal = glm::angleAxis(radiansHorizonal, this->game->worldUp);
	this->offsetFromTarget = rotationHorizonal * this->offsetFromTarget;

	// vertical
	glm::quat rotationVertical = glm::angleAxis(radiansVertical, camera->right);
	glm::vec3 tempOffset = rotationVertical * this->offsetFromTarget;
	float radiansToWorldUp = glm::dot(glm::normalize(tempOffset), this->game->worldUp);
	if (radiansToWorldUp < this->verticalRadiansMax && radiansToWorldUp > this->verticalRadiansMin)
		this->offsetFromTarget = tempOffset;
}


/*------------------------------------------------------------------------------
< zoom >
------------------------------------------------------------------------------*/
void CameraController::zoom(float distance) {
	Camera* camera = this->camera->getComponent<Camera>();

	glm::vec3 zoomDistance = camera->front * distance;
	glm::vec3 tempOffset = this->offsetFromTarget + zoomDistance;
	float length2 = glm::length2(tempOffset);
	if (length2 > this->offsetFromTargetMin && length2 <= this->offsetFromTargetMax)
		this->offsetFromTarget = tempOffset;
}
