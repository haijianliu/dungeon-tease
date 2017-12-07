
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Scene::Scene() {
	this->game = Game::getInstance();
	this->renderLayer = new RenderLayer();
	this->fxLayer = new RenderLayer();
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Scene::~Scene() {
	deleteVector(this->gameObjects);
	delete this->renderLayer;
	delete this->fxLayer;
}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void Scene::update() {

}


/*------------------------------------------------------------------------------
 < start scene > for scene manager
------------------------------------------------------------------------------*/
void Scene::startScene() {
	this->start();
	for (unsigned int i = 0; i < this->gameObjects.size(); i++) {
		this->gameObjects[i]->start();
		// mesh renderring list
		MeshRenderer* meshRenderer = this->gameObjects[i]->getComponent<MeshRenderer>();
		if (meshRenderer && meshRenderer->castShadow)
			this->shadowQueue.push_back(meshRenderer);
		if (meshRenderer) {
			if (meshRenderer->renderLayer == RENDER_LAYER_DEFAULT)
				this->renderLayer->add(this->gameObjects[i]);
			if (meshRenderer->renderLayer == RENDER_LAYER_FX)
				this->fxLayer->add(this->gameObjects[i]);
			this->renderQueue.push_back(meshRenderer);
		}
		// point lights list
		PointLight* pointLight = this->gameObjects[i]->getComponent<PointLight>();
		if (pointLight)
			this->pointLights.push_back(pointLight);
	}
	this->started = true;
}


/*------------------------------------------------------------------------------
 < update scene > for scene manager
------------------------------------------------------------------------------*/
void Scene::updateScene() {
	// user scene update
	this->update();

	// game objects update
	for (unsigned int i = 0; i < this->gameObjects.size(); i++)
		if (this->gameObjects[i]->active)
			this->gameObjects[i]->update();

	// frustum culling
	FrustumCulling* frustumCulling = this->mainCamera->getComponent<FrustumCulling>();
	if (frustumCulling) {
		for (unsigned int i = 0; i < this->renderQueue.size(); i++)
			frustumCulling->cullingSphere(this->renderQueue.at(i));
		for (unsigned int i = 0; i < this->pointLights.size(); i++)
			frustumCulling->cullingSphere(this->pointLights.at(i));
	}

	// shadow mapping
	if (this->shadowQueue.size() > 0)
		this->game->shadowMapping->render(&this->shadowQueue);

	// final render
	this->game->renderPass->render(this->renderLayer, this->fxLayer, &this->pointLights, this->mainCamera);
	// this->game->renderPass->renderBounding(&this->renderQueue, this->mainCamera);
}


/*------------------------------------------------------------------------------
< add gameobject >
------------------------------------------------------------------------------*/
void Scene::addGameObject(const char* name, GameObject* gameObject) {
	gameObject->scene = this;
	this->gameObjects.push_back(gameObject);
	this->gameObjectsMapping.insert(std::make_pair(name, this->index));
	this->index ++;
}


/*------------------------------------------------------------------------------
< get gameobject >
------------------------------------------------------------------------------*/
GameObject* Scene::getGameObject(const char* name) {
	auto it = this->gameObjectsMapping.find(name);
	if (it != this->gameObjectsMapping.end())
		return this->gameObjects[it->second];
	else
		return nullptr;
}
