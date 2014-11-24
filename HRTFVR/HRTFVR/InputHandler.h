#pragma once
#include <GLFW\glfw3.h>

class InputHandler
{
public:
	InputHandler();
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	~InputHandler();
};

