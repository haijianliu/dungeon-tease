
#ifndef Window_hpp
#define Window_hpp

class Window {
private:
	GLFWwindow* createWindow(const char* name, int screenWidth, int screenHeight);

public:
	// GLFWwindow
	GLFWwindow* window;
	// window information
	int screenWidth, screenHeight;
	float retina;

	Window(const char* name, int screenWidth, int screenHeight);
	~Window();

	void getWindowSize();
};

#endif /* Window_hpp */
