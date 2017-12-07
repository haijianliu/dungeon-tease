
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
PlayerController::PlayerController() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
PlayerController::~PlayerController() {

}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void PlayerController::update() {
	Transform* playerTransform = this->gameObject->getComponent<Transform>();

	glm::vec3 direction = playerTransform->front(); // if no input deflaut the last direction
	glm::vec3 axisLS = game->input->getAxisLS();

	glm::vec3 cameraFrontFromWorldUp = glm::normalize(glm::cross(this->camera->getComponent<Camera>()->right, this->game->worldUp));
	glm::quat worldToCamera = glm::rotation(glm::vec3(0,0,1), cameraFrontFromWorldUp);


	if (game->time->currentTime - this->lastAttack > 3.0) {
		if (abs(axisLS.x) > 0.6 || abs(axisLS.z) > 0.6) {
			direction = worldToCamera * game->input->getNormalLS();
			axisLS = worldToCamera * axisLS;

			playerTransform->position.x += 4 * axisLS.x * game->time->deltaTime;
			playerTransform->position.z += 4 * axisLS.z * game->time->deltaTime;

			this->animation = 3;
		}
		else if (abs(axisLS.x) > 0.1 || abs(axisLS.z) > 0.1){
			direction = worldToCamera * game->input->getNormalLS();
			axisLS = worldToCamera * axisLS;

			playerTransform->position.x += 2 * axisLS.x * game->time->deltaTime;
			playerTransform->position.z += 2 * axisLS.z * game->time->deltaTime;

			this->animation = 2;
		}
		else {
			this->animation = 0;
		}
	}

	if (game->input->getJoystickTrigger(JOY_L1)) {
		this->animation = 4;
		this->lastAttack = game->time->currentTime;
	}
	
	if (game->input->getJoystickPress(JOY_TRIANGLE)) {
		playerTransform->position.y += 4 * game->time->deltaTime;
	}
	if (game->input->getJoystickPress(JOY_CROSS)) {
		playerTransform->position.y -= 4 * game->time->deltaTime;
	}

	playerTransform->rotate(direction, 2 * PI * game->time->deltaTime);

    MeshRenderer* playerMeshRenderer =  this->gameObject->getComponent<MeshRenderer>();
    if (playerMeshRenderer)
        playerMeshRenderer->model->updatePose(this->animation, game->time->currentTime);
}
