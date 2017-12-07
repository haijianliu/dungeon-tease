
#include "Engine.hpp"

/*------------------------------------------------------------------------------
< Constructor >
------------------------------------------------------------------------------*/
Window::Window(const char* name, int screenWidth, int screenHeight) {
	this->window = createWindow(name,screenWidth,screenHeight);
	glfwGetFramebufferSize(this->window, &this->screenWidth, &this->screenHeight);
	this->retina = this->screenWidth / SCREEN_WIDTH;
}


/*------------------------------------------------------------------------------
< Destructor >
------------------------------------------------------------------------------*/
Window::~Window() {

}


/*------------------------------------------------------------------------------
< createWindow >
------------------------------------------------------------------------------*/
GLFWwindow* Window::createWindow(const char* name, int screenWidth, int screenHeight) {

	// Create OpenGL Window
	GLFWwindow* window;

	// Initialise GLFW
	if (!glfwInit()) {
		printf("[GLFW] Failed to initialize GLFW\n"); // Debug information
		return NULL;
	}

	// Default window settings
	glfwWindowHint(GLFW_SAMPLES, 0); // antialiasing
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE); // lock screen size
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // don't want the old OpenGL

	// Open a window and create its OpenGL context
	window = glfwCreateWindow(screenWidth,screenHeight,name,NULL,NULL);
	if (window == NULL) {
		printf("[GLFW] Failed to open GLFW window.\n"); // Debug information
		glfwTerminate();
		return NULL;
	}
	glfwMakeContextCurrent(window);

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		printf("[GLEW] Failed to initialize GLEW\n"); // Debug information
		glfwTerminate();
		return NULL;
	}

	printf("[GLEW] Created a OpenGL Window: %s <%d,%d>\n",name,screenWidth,screenHeight); // Debug information


	// Other Default settings
	// background
	glClearColor(0.0,0.0,0.0,0.0);
	// Set input mode GLFW_STICKY_KEYS
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	// glDepthFunc(GL_LESS);
	// set depth function to less than AND equal for skybox depth trick.
	glDepthFunc(GL_LEQUAL);
	// enable seamless cubemap sampling for lower mip levels in the pre-filter map.
//	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	// Cull triangles which normal is not towards the camera
	glEnable(GL_CULL_FACE);
	// Enable alpha channel
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	return window;
}


/*------------------------------------------------------------------------------
< getWindowSize >
------------------------------------------------------------------------------*/
void Window::getWindowSize() {
	glfwGetFramebufferSize(this->window, &this->screenWidth, &this->screenHeight);
}
