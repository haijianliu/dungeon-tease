
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Time::Time() {

}

Time* Time::getInstance() {
	static Time* time = new Time();
	return time;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Time::~Time() {

}


/*------------------------------------------------------------------------------
< update >
------------------------------------------------------------------------------*/
void Time::update() {
	this->currentTime = glfwGetTime();
	this->deltaTime = this->currentTime - this->lastTime;
	// this->deltaTime > 0.032 ? 0.032 : this->deltaTime; // 30 FPS lastest
	this->lastTime = this->currentTime;
	// std::cout << this->deltaTime << '\n';
}
