
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
FxTorchFire::FxTorchFire() {

}

FxTorchFire* FxTorchFire::getInstance() {
	static FxTorchFire* instance;
	return instance;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
FxTorchFire::~FxTorchFire() {

}


/*------------------------------------------------------------------------------
< create prefab >
------------------------------------------------------------------------------*/
void FxTorchFire::createPrefab(std::string name, glm::mat4 model, Scene* scene) {
	Game* game = Game::getInstance();
	glm::vec3 positon = model * glm::vec4(0, 0, 0, 1);

	// smoke emitter
	GameObject* smoke = new GameObject();
	Transform* smokeTransform = smoke->addComponent<Transform>();
	smokeTransform->position = positon;
	Emitter* smokeEmitter = smoke->addComponent<Emitter>();
	smokeEmitter->material = game->resources->getMaterial("fx_fire_smoke");
	smokeEmitter->maxParticles = 20;
	smokeEmitter->spawnTime = 0.01;
	smokeEmitter->minLifeTime = 1;
	smokeEmitter->maxLifeTime = 2;
	smokeEmitter->initScale = 10 * GLOBAL_SCALE;
	smokeEmitter->velocityHorizonalRange = 0.05;
	smokeEmitter->velocityVerticalRange = 0;
	smokeEmitter->gravity = -0.3;
	smokeEmitter->createParticles((name + "_fire_smoke_particle").c_str(), scene);
	scene->addGameObject((name + "_fire_smoke_emitter").c_str(), smoke);

	// fire emitter
	GameObject* fire = new GameObject();
	Transform* fireTransform = fire->addComponent<Transform>();
	fireTransform->position = positon;
	Emitter* fireEmitter = fire->addComponent<Emitter>();
	fireEmitter->material = game->resources->getMaterial("fx_fire");
	fireEmitter->animation = true;
	fireEmitter->divideX = 4;
	fireEmitter->divideY = 4;
	fireEmitter->sampleTime = 0.1;
	fireEmitter->maxParticles = 26;
	fireEmitter->spawnTime = 0.01;
	fireEmitter->minLifeTime = 1;
	fireEmitter->maxLifeTime = 1.5;
	fireEmitter->initScale = 10 * GLOBAL_SCALE;
	fireEmitter->velocityHorizonalRange = 0.05;
	fireEmitter->velocityVerticalRange = 0.1;
	fireEmitter->gravity = -0.5;
	fireEmitter->createParticles((name + "_fire_particle").c_str(), scene);
	scene->addGameObject((name + "_fire_emitter").c_str(), fire);

	// spark emitter
	GameObject* spark = new GameObject();
	Transform* sparkTransform = spark->addComponent<Transform>();
	sparkTransform->position = positon;
	Emitter* sparkEmitter = spark->addComponent<Emitter>();
	sparkEmitter->material = game->resources->getMaterial("fx_fire_spark");
	sparkEmitter->maxParticles = 40;
	sparkEmitter->spawnTime = 0.01;
	sparkEmitter->minLifeTime = 1;
	sparkEmitter->maxLifeTime = 2;
	sparkEmitter->initScale = GLOBAL_SCALE;
	sparkEmitter->velocityHorizonalRange = 0.1;
	sparkEmitter->velocityVerticalRange = 0.1;
	sparkEmitter->gravity = -0.5;
	sparkEmitter->createParticles((name + "_spark_particle").c_str(), scene);
	scene->addGameObject((name + "_spark_emitter").c_str(), spark);

	// drop emitter
	GameObject* drop = new GameObject();
	Transform* dropTransform = drop->addComponent<Transform>();
	dropTransform->position = positon;
	Emitter* dropEmitter = drop->addComponent<Emitter>();
	dropEmitter->material = game->resources->getMaterial("fx_fire_drop");
	dropEmitter->maxParticles = 8;
	dropEmitter->spawnTime = 0.01;
	dropEmitter->minLifeTime = 0.5;
	dropEmitter->maxLifeTime = 1.5;
	dropEmitter->initScale = 2 * GLOBAL_SCALE;
	dropEmitter->velocityHorizonalRange = 0.05;
	dropEmitter->velocityVerticalRange = 0.1;
	dropEmitter->gravity = 0.8;
	dropEmitter->createParticles((name + "_drop_particle").c_str(), scene);
	scene->addGameObject((name + "_drop_emitter").c_str(), drop);

	// point light
	GameObject* light = new GameObject();
	Transform* lightTransform = light->addComponent<Transform>();
	lightTransform->position = positon;
	PointLight* lightPointLight = light->addComponent<PointLight>();
	lightPointLight->color = glm::vec3(1, 0.4, 0.1);
	lightPointLight->intensity = 2;
	scene->addGameObject((name + "light").c_str(), light);
}
