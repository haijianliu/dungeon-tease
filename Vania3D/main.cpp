#include "Engine.hpp"


/*==============================================================================
< main >
==============================================================================*/
int main() {
	Game* game = Game::getInstance();
	game->start();

	// Game Loop
	while (!glfwWindowShouldClose(game->window->window)) {
		if (glfwGetKey(game->window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS) glfwSetWindowShouldClose(game->window->window, true);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		game->update();
		glfwSwapBuffers(game->window->window);
		glfwPollEvents();
	}

	delete game;
	glfwTerminate(); // glfw: terminate, clearing all previously allocated GLFW resources.
	return 0;
}

