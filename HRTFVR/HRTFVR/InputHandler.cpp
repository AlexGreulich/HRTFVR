#include "InputHandler.h"
#include <iostream>

using namespace std;

InputHandler::InputHandler()
{
}

void InputHandler::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
	cout << "Key: " << key;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

InputHandler::~InputHandler()
{
}
