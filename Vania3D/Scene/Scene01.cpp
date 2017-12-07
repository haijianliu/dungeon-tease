
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene01::Scene01() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene01::~Scene01() {

}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void Scene01::start() {
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
	GameObject* light = new GameObject();
	light->staticObject = false;
	Transform* lightTransform = light->addComponent<Transform>();
	Offset* lightTarget = light->addComponent<Offset>();
	lightTarget->offsetPosition = glm::vec3(0, 2.5, 0);
	lightTarget->parent = playerTransform;
	PointLight* pointLight = light->addComponent<PointLight>();
	pointLight->color = glm::vec3(5);
	this->addGameObject("PlayerLight", light);

//	Level* level = new Level("./Assets/Models/Kowloon/map.fbx");
//	level->createGameObjects(this);
//	delete level;

	Map* map = new Map(this, "./Assets/Models/InfinityBladeGrassLands/Maps/ElvenRuinsMap.fbx");
	delete map;

	// light
//	GameObject* light[4];
//	for (int i = 0; i < 4; i++) {
//		light[i] = new GameObject();
//		Transform* lightTransform = light[i]->addComponent<Transform>();
//		lightTransform->modelScale = glm::vec3(0.1);
//		light[i]->addComponent<PointLight>();
//		this->addGameObject(("light" + std::to_string(i)).c_str(), light[i]);
//	}
//	light[0]->getComponent<Transform>()->position = glm::vec3( 2.0f,  2.0f,  2.0f);
//	light[1]->getComponent<Transform>()->position = glm::vec3( 2.0f,  2.0f, -2.0f);
//	light[2]->getComponent<Transform>()->position = glm::vec3(-2.0f,  2.0f,  2.0f);
//	light[3]->getComponent<Transform>()->position = glm::vec3(-2.0f,  2.0f, -2.0f);
//	light[0]->getComponent<PointLight>()->color = glm::vec3(10.0f, 10.0f, 10.0f);
//	light[1]->getComponent<PointLight>()->color = glm::vec3(10.0f, 0.0f, 0.0f);
//	light[2]->getComponent<PointLight>()->color = glm::vec3(0.0f, 10.0f, 0.0f);
//	light[3]->getComponent<PointLight>()->color = glm::vec3(0.0f, 0.0f, 10.0f);

	
	// Enable alpha channel after generate prefilter map
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

