
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Emitter::Emitter() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Emitter::~Emitter() {

}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void Emitter::update() {
	if (game->time->currentTime > this->lastSpawnTime + this->spawnTime) {
		this->activeParticle();
		this->lastSpawnTime = game->time->currentTime;
	}
}


/*------------------------------------------------------------------------------
< create particles >
create particles game objects and add them to scene render lise
------------------------------------------------------------------------------*/
void Emitter::createParticles(const char* name, Scene* scene) {
	std::string particleName = std::string(name);
	game->resources->loadModel(particleName.c_str(), MESH_ATTRIBUTE_INSTANCE_FX, "./Assets/Models/Basic/quad.fbx"); // reload new model for seperate emitters
	for (unsigned int i = 0; i < this->maxParticles; i++) {
		GameObject* particle = new GameObject();
		particle->staticObject = false;
		particle->active = false;
		Transform* particleTransform = particle->addComponent<Transform>();
		MeshRenderer* particleMeshRenderer = particle->addComponent<MeshRenderer>();
		particleMeshRenderer->model = game->resources->getModel(particleName);
		particleMeshRenderer->materials.push_back(this->material);
		particleMeshRenderer->renderLayer = RENDER_LAYER_FX;
		particle->addComponent<Billboard>();
		Particle* particleComponent = particle->addComponent<Particle>();
		if (this->animation) {
			UVAnimation* particleUVAnimation = new UVAnimation(this->divideX, this->divideY, this->sampleTime);
			particle->addComponent(particleUVAnimation);
		}
		scene->addGameObject((particleName + std::to_string(i)).c_str(), particle);
		this->particles.push_back(particleComponent);
	}
}


/*------------------------------------------------------------------------------
< active particle by spawn time >
------------------------------------------------------------------------------*/
void Emitter::activeParticle() {
	for (unsigned int i = 0; i < this->particles.size(); i++) {
		if (!this->particles[i]->gameObject->active) {
			// set gameobject
			this->particles[i]->gameObject->active = true;
			this->particles[i]->gameObject->lastActiveTime = game->time->currentTime;
			this->particles[i]->gameObject->transform->position = this->gameObject->transform->position;
			// particle settings
			this->particles[i]->lifeTime = glm::linearRand(this->minLifeTime, this->maxLifeTime);
			this->particles[i]->initScale = glm::vec3(this->initScale);
			this->particles[i]->initVelocity = glm::vec3(glm::linearRand(-this->velocityHorizonalRange, this->velocityHorizonalRange), glm::linearRand(-this->velocityVerticalRange, this->velocityVerticalRange), glm::linearRand(-this->velocityHorizonalRange, this->velocityHorizonalRange));
			this->particles[i]->gravity = this->gravity;

			return;
		}
	}
}
