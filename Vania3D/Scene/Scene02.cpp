
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene02::Scene02() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene02::~Scene02() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void Scene02::start() {
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
	playerTransform->position = glm::vec3(0, 0, 0);
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

	Map* map = new Map(this, "./Assets/Models/FantasyDungeon/Maps/Map.fbx");
	delete map;

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
	light[0]->getComponent<Transform>()->position = glm::vec3(4.5, 2.5, 0);
	light[1]->getComponent<Transform>()->position = glm::vec3(1.5, 2, 0);
	light[2]->getComponent<Transform>()->position = glm::vec3(0, 2, 0);
	light[3]->getComponent<Transform>()->position = glm::vec3(-1.5, 2, 0);
	light[0]->getComponent<PointLight>()->color = glm::vec3(2, 4, 5);
//	light[1]->getComponent<PointLight>()->color = glm::vec3(20.0f, 0.0f, 0.0f);
//	light[2]->getComponent<PointLight>()->color = glm::vec3(0.0f, 20.0f, 0.0f);
//	light[0]->getComponent<PointLight>()->color = glm::vec3(0.0f, 0.0f, 0.0f);
//	light[1]->getComponent<PointLight>()->color = glm::vec3(0.0f, 0.0f, 0.0f);
//	light[2]->getComponent<PointLight>()->color = glm::vec3(0.0f, 0.0f, 0.0f);
	light[3]->getComponent<PointLight>()->color = glm::vec3(5, 10, 15);


//	GameObject* light2[10];
//	for (int i = 0; i < 5; i++) {
//		light2[i] = new GameObject();
//		light2[i]->staticObject = false;
//		Transform* lightTransform = light2[i]->addComponent<Transform>();
//		light2[i]->addComponent<PointLight>();
//		this->addGameObject(("light2" + std::to_string(i)).c_str(), light2[i]);
//	}

}

