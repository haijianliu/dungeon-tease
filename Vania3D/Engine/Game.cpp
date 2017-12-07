
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Game::Game() {

}

Game* Game::getInstance() {
	static Game* game = new Game();
	return game;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Game::~Game() {
	delete this->window;
	delete this->resources;
	delete this->sceneManager;
	delete this->renderPass;
	delete this->shadowMapping;
	delete this->time;
	delete this->input;
}


/*------------------------------------------------------------------------------
< start >
------------------------------------------------------------------------------*/
void Game::start() {
	/* create objects */
	this->window = new Window("vania", SCREEN_WIDTH, SCREEN_HEIGHT);
	this->resources = Resources::getInstance();
	this->time = Time::getInstance();
	this->input = Input::getInstance();

	// resources
	this->resources->start();

	// render pass
	this->renderPass = new RenderPass();
	this->renderPass->start();
	// shadow mapping
	this->shadowMapping = new ShadowMapping();
	this->shadowMapping->start();

	// create scenes
	this->sceneManager = new SceneManager();
	this->sceneManager->addScene("Scene00", new Scene00());
	this->sceneManager->addScene("Scene01", new Scene01());
	this->sceneManager->addScene("Scene02", new Scene02());
	this->sceneManager->addScene("Scene03", new Scene03());
	this->sceneManager->addScene("Scene04", new Scene04());
	this->sceneManager->addScene("Scene05", new Scene05());
	this->sceneManager->setActiveScene("Scene03"); // set default scene
}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void Game::update() {
	// keep in order
	this->time->update();
	this->input->updateJoystick();
	this->sceneManager->update();
}
