
#include "Engine.hpp"



// Returns a quaternion that will make your object looking towards 'direction'.
// Similar to RotationBetweenVectors, but also controls the vertical orientation.
// This assumes that at rest, the object faces +Z.
// Beware, the first parameter is a direction, not the target point !

//glm::quat LookAt(glm::vec3 direction, glm::vec3 desiredUp){
//
//	if (length2(direction) < 0.0001f )
//		return glm::quat();
//
//	// Recompute desiredUp so that it's perpendicular to the direction
//	// You can skip that part if you really want to force desiredUp
//	glm::vec3 right = cross(direction, desiredUp);
//	desiredUp = cross(right, direction);
//
//	// Find the rotation between the front of the object (that we assume towards +Z,
//	// but this depends on your model) and the desired direction
//	glm::quat rot1 = rotationBetweenVectors(glm::vec3(0.0f, 0.0f, 1.0f), direction);
//	// Because of the 1rst rotation, the up is probably completely screwed up.
//	// Find the rotation between the "up" of the rotated object, and the desired up
//	glm::vec3 newUp = rot1 * glm::vec3(0.0f, 1.0f, 0.0f);
//	glm::quat rot2 = rotationBetweenVectors(newUp, desiredUp);
//
//	// Apply them
//	return rot2 * rot1; // remember, in reverse order.
//}


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene00::Scene00() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene00::~Scene00() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void Scene00::start() {
	Game* game = Game::getInstance();

	// camera
	GameObject* camera = new GameObject();
	camera->staticObject = false;
	camera->addComponent<Camera>();
	
	// player
	GameObject* player = new GameObject();
	player->staticObject = false;
	Transform* playerTransform = player->addComponent<Transform>();
	playerTransform->modelScale = glm::vec3(GLOBAL_SCALE);
	playerTransform->position = glm::vec3(0, -0.6, 0);
	PlayerController* playerController = player->addComponent<PlayerController>();
	playerController->camera = camera;
	CameraController* cameraController = player->addComponent<CameraController>();
	cameraController->camera = camera;
	MeshRenderer* playerMeshRenderer = player->addComponent<MeshRenderer>();
	playerMeshRenderer->model = game->resources->getModel("player");
	playerMeshRenderer->materials.push_back(game->resources->getMaterial("player"));
	playerMeshRenderer->castShadow = true;
	this->addGameObject("player", player);
	game->shadowMapping->target = player;
	
	// camera target
	GameObject* cameraTarget = new GameObject();
	Transform* cameraTargetTransform = cameraTarget->addComponent<Transform>();
	Offset* cameraTargetOffset = cameraTarget->addComponent<Offset>();
	cameraTargetOffset->parent = playerTransform;
	cameraTargetOffset->offsetPosition = glm::vec3(0, 1, 0);
	this->addGameObject("cameraTarget", cameraTarget);
	
	// camera
	Transform* cameraTransform = camera->addComponent<Transform>();
	cameraTransform->position = glm::vec3(0.0,2.0,4.0);
	camera->getComponent<Camera>()->target = cameraTargetTransform;
	camera->addComponent<FrustumCulling>();
	this->mainCamera = camera;
	this->addGameObject("mainCamera", camera);

	// light
	GameObject* light[4];
	for (int i = 0; i < 4; i++) {
		light[i] = new GameObject();
		light[i]->staticObject = false;
		Transform* lightTransform = light[i]->addComponent<Transform>();
		lightTransform->modelScale = glm::vec3(5 * GLOBAL_SCALE);
		light[i]->addComponent<PointLight>();
		// for test
		MeshRenderer* lightMeshRenderer = light[i]->addComponent<MeshRenderer>();
		lightMeshRenderer->model = game->resources->getModel("sphere");
		lightMeshRenderer->materials.push_back(game->resources->getMaterial("simple"));
		this->addGameObject(("light" + std::to_string(i)).c_str(), light[i]);
	}
	light[0]->getComponent<Transform>()->position = glm::vec3( 3.0f,  2,  3.0f);
	light[1]->getComponent<Transform>()->position = glm::vec3( 3.0f,  2, -3.0f);
	light[2]->getComponent<Transform>()->position = glm::vec3(-3.0f,  2,  3.0f);
	light[3]->getComponent<Transform>()->position = glm::vec3(-3.0f,  2, -3.0f);
	light[0]->getComponent<PointLight>()->color = glm::vec3(20.0f, 20.0f, 20.0f);
	light[1]->getComponent<PointLight>()->color = glm::vec3(20.0f, 0.0f, 0.0f);
	light[2]->getComponent<PointLight>()->color = glm::vec3(0.0f, 20.0f, 0.0f);
	light[3]->getComponent<PointLight>()->color = glm::vec3(0.0f, 0.0f, 20.0f);


	//kernel
	//	std::vector<glm::vec3> ssaoKernel = genSSAOKernel(4);
	//	for (unsigned int i = 0; i < ssaoKernel.size(); ++i)
	//		game->resources->getShader("renderPass")->setVec3(("samples[" + std::to_string(i) + "]").c_str(), ssaoKernel[i]);
	// noiseTexture
	//	unsigned int noiseTexture = genNoiseTexture(4);
	//	glActiveTexture(GL_TEXTURE9);
	//	glBindTexture(GL_TEXTURE_2D, noiseTexture);
	//	game->resources->getShader("renderPass")->setInt("texNoise", 9);


	// Enable alpha channel after generate prefilter map
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

}

