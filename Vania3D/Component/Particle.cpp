
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Particle::Particle() {

}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Particle::~Particle() {

}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void Particle::update() {
	float particleTime = game->time->currentTime - this->gameObject->lastActiveTime;
	if (particleTime > this->lifeTime)
		this->gameObject->active = false;
	// position
	this->initVelocity.y -= this->gravity * game->time->deltaTime;
	this->gameObject->transform->position += this->initVelocity * game->time->deltaTime;
	// scale over life (sin)
	float factor = particleTime / this->lifeTime; // 0 >> 1
	this->gameObject->transform->scale = this->initScale * (float)glm::sin(PI * factor);
}
