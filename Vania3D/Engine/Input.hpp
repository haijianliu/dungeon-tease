
#ifndef Input_hpp
#define Input_hpp

enum PS4_CONTROLLER {
	JOY_SQUARE, JOY_CROSS, JOY_CIRCLE, JOY_TRIANGLE,
	JOY_L1, JOY_R1, JOY_L2, JOY_R2,
	JOY_SHARE, JOY_OPTION,
	JOY_L3, JOY_R3, JOY_HOME, JOY_TOUCHPAD,
	JOY_UP, JOY_RIGHT, JOY_DOWN, JOY_LEFT
};

class Input {
private:
	// joystick status
	int joyButtonCount, joyEvent = GLFW_DISCONNECTED, joyConnect = 0;
	// joystick data container
	int joyButtons[25] = {GLFW_RELEASE};
	glm::vec3 normalLS = glm::vec3(0.0); // direction normal in world space
	glm::vec3 normalRS = glm::vec3(0.0); // direction normal in world space
	glm::vec3 axisLS = glm::vec3(0.0); // direction in world space
	glm::vec3 axisRS = glm::vec3(0.0); // direction in world space
	float axisL2 = 0;
	float axisR2 = 0;

	// keyboard data container
	int keys[GLFW_KEY_LAST] = {GLFW_RELEASE};

	Input();

public:
	// controller properties
	float gravity = 3.0; // speed in units per second that the axis falls toward neutral when no buttons are pressed
	float deadzone = 0.25; // size of the analog dead zone, all analog device values within this range result map to neutral
	float sensitivity = 3.0; // speed in units per second that the the axis will move toward the target value, this is for digital devices only
	bool snap = true; // if enabled, the axis value will reset to zero when pressing a button of the opposite direction

	// constructor
	static Input* getInstance();
	~Input();

	// callback
	void joystickcallback(int joy, int event);
	void keycallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	// update joystick buttons and axis data in every game frame
	void updateJoystick();

	// joystick get methods
	bool getJoystickPress(int button);
	bool getJoystickTrigger(int button);
	glm::vec3 getAxisLS();
	glm::vec3 getNormalLS();
	glm::vec3 getAxisRS();
	glm::vec3 getNormalRS();

	// keyboard get methods
	bool getButtonPress(int button);
	bool getButtonTrigger(int button);
};

#endif /* Input_hpp */
