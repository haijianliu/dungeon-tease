
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< callback >
------------------------------------------------------------------------------*/
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	Input::getInstance()->keycallback(window,key,scancode,action,mods);
}

void joystickCallback(int joy, int event) {
	Input::getInstance()->joystickcallback(joy,event);
}

Input* Input::getInstance() {
	static Input* instance = new Input();
	return instance;
}

void Input::keycallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	this->keys[key] = action;
	if(action == GLFW_REPEAT ) {
		std::cout << "GLFW_REPEAT" << key << std::endl;
	} else if (action == GLFW_PRESS) {
		std::cout << "GLFW_PRESS" << key << std::endl;
	} else if (action == GLFW_RELEASE) {
		std::cout << "GLFW_RELEASE" << key << std::endl;
	}
}

void Input::joystickcallback(int joy, int event) {
	this->joyEvent = event;
	this->joyConnect = joy;
	if (event == GLFW_CONNECTED) {
		std::cout << "GLFW_CONNECTED : " << joy << std::endl;
	}
	if (event == GLFW_DISCONNECTED) {
		std::cout << "GLFW_DISCONNECTED : " << joy << std::endl;
	}
}


/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Input::Input() {
	Game* game = Game::getInstance();
	glfwSetKeyCallback(game->window->window, keyCallback);
	glfwSetJoystickCallback(joystickCallback);
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Input::~Input() {

}


/*------------------------------------------------------------------------------
< update joystick >
update joystick buttons and axis data in every game frame (called by engine core)
------------------------------------------------------------------------------*/
void Input::updateJoystick() {
	if (this->joyEvent == GLFW_CONNECTED) {
		/* buttons */
		const unsigned char* buttons = glfwGetJoystickButtons(this->joyConnect, &this->joyButtonCount);
		for (int i = 0; i < this->joyButtonCount; i++) {
			if (buttons[i] == GLFW_PRESS && (this->joyButtons[i] == GLFW_PRESS || this->joyButtons[i] == GLFW_REPEAT)) {
				this->joyButtons[i] = GLFW_REPEAT;
			}
			else {
				this->joyButtons[i] = buttons[i];
			}
		}

		/* axis */
		// get input data
		int axesCount;
		const float* joyAxis = glfwGetJoystickAxes(this->joyConnect, &axesCount);

		/* scaled radial dead zone */

		// LS
		this->axisLS = glm::vec3(joyAxis[0], 0.0, joyAxis[1]);
		float magnitudeLS = glm::length(this->axisLS);
		if(magnitudeLS < this->deadzone) {
			this->normalLS = glm::vec3(0.0);
			this->axisLS = glm::vec3(0.0);
		}
		else {
			this->normalLS = glm::normalize(this->axisLS);
			this->axisLS = this->normalLS * ((magnitudeLS - this->deadzone) / (1 - this->deadzone));
		}
		// RS
		this->axisRS = glm::vec3(joyAxis[2], 0.0, joyAxis[3]);
		float magnitudeRS = glm::length(this->axisRS);
		if(magnitudeRS < this->deadzone) {
			this->normalRS = glm::vec3(0.0);
			this->axisRS = glm::vec3(0.0);
		}
		else {
			this->normalRS = glm::normalize(this->axisRS);
			this->axisRS = this->normalRS * ((magnitudeRS - this->deadzone) / (1 - this->deadzone));
		}

		// L2 R2
		this->axisL2 = joyAxis[4];
		this->axisL2 = joyAxis[5];
	}
}


/*------------------------------------------------------------------------------
< keyboard get methods >
------------------------------------------------------------------------------*/
bool Input::getButtonPress(int button) {
	if (this->keys[button] == GLFW_PRESS || this->keys[button] == GLFW_REPEAT) return true;
	else return false;
}

bool Input::getButtonTrigger(int button) {
	if (this->keys[button] == GLFW_PRESS) {
		this->keys[button] = GLFW_REPEAT; return true;
	}
	else return false;
}


/*------------------------------------------------------------------------------
< joystick get methods >
------------------------------------------------------------------------------*/
bool Input::getJoystickPress(int button) {
	if (this->joyButtons[button] == GLFW_PRESS || this->joyButtons[button] == GLFW_REPEAT) return true;
	else return false;
}

bool Input::getJoystickTrigger(int button) {
	if (this->joyButtons[button] == GLFW_PRESS) return true;
	else return false;
}

glm::vec3 Input::getAxisLS() {
	return this->axisLS;
}

glm::vec3 Input::getNormalLS() {
	return this->normalLS;
}

glm::vec3 Input::getAxisRS() {
	return this->axisRS;
}

glm::vec3 Input::getNormalRS() {
	return this->normalRS;
}
