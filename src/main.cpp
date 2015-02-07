#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>

#include "Display.h"
#include "Shader.h"
#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"
#include "Mesh.h"
#include "Game.h"
#include "Logger.h"

static const int DISPLAY_WIDTH = 800;
static const int DISPLAY_HEIGHT = 600;

INITIALIZE_EASYLOGGINGPP

// static proxy function to propagate the key events to the display instance
static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	Game * game = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));
	game->HandleKey(key, scancode, action, mods);
}

// static proxy function to propagate the mouse position events to the display instance
static void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos){
	Game * game = reinterpret_cast<Game *>(glfwGetWindowUserPointer(window));
	game->HandleMouse(xpos, ypos);
}

int main(int argc, const char** argv){

	START_EASYLOGGINGPP(argc, argv);

	// configure logger
	el::Loggers::reconfigureAllLoggers(
		el::ConfigurationType::Format,
		"[%level] %msg"
	);

    // Setup OpenGL context
	Display display(800, 600, "HRTFVR");
	Game game(&display);

	// bind display pointer to window
	// so we can cast the pointer to an instance
	glfwSetWindowUserPointer(display.getWindow(), &game);

	// bind keyCallback
	glfwSetKeyCallback(display.getWindow(), keyCallback);
	glfwSetCursorPosCallback(display.getWindow(), mouseMoveCallback);

	// run until the window should close
	while ( !glfwWindowShouldClose( display.getWindow()) ){
		
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		game.Update();

		display.Update();
	}

	return 0;
}
