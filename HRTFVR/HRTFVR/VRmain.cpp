#include "VRmain.h"
#include <GL/glew.h>  
//#include <GL/glxew.h>
#include <GLFW/glfw3.h>  
#include <glm.hpp>
#include <stdio.h>  
#include <stdlib.h>  
#include <iostream>

const GLuint windowWidth = 800;
const GLuint windowHeight = 600;


VRmain::VRmain(){

}
VRmain::~VRmain() {
	destroyAndCleanse();

}

//Define an error callback  
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

//Define the key input callback  
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void VRmain::init() {
	// If no Rift is connected, useRift is false
	useRift = oculus->initialize();
	sceneManager = new SceneManager();
	renderer = new Renderer(windowWidth, windowHeight);
	// On construction create new OVR- Handler, needs to be destroyed
	oculus = new OculusHandler();
	std::cout << "init";
}

void VRmain::destroyAndCleanse(){
	oculus->destroyHMD();
}

int main(void)
{
	VRmain *vrmain = new VRmain();
	//Set the error callback  
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW  
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version  
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2); //Request a specific OpenGL version  
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing  
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);  //GLFW_OPENGL_CORE_PROFILE



	//Declare a window object  
	GLFWwindow* window;

	//Create a window and create its OpenGL context  
	window = glfwCreateWindow(windowWidth, windowHeight, "Test Window", NULL, NULL);

	//If the window couldn't be created  
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread.   
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();

	if (glewError != GLEW_OK)
	{
		std::cout << glewError;
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	vrmain->init();

	//Sets the key callback  
	glfwSetKeyCallback(window, key_callback);

	//Set a background color  
	glClearColor(0.0f, 0.0f, 1.0f, 0.0f);

	//Main Loop  
	do
	{
		//Clear color buffer  
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		//GLuint a = vrmain->loader->getMeshByName("cube.obj");
		vrmain->renderer->render("cube.obj"); //renderer.render(loader);

		/*

		RENDER AND AUDIO Code GOES HERE

		*/

		//Swap buffers  
		glfwSwapBuffers(window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...  
		glfwPollEvents();

	} //Check if the ESC key had been pressed or if the window had been closed  
	while (!glfwWindowShouldClose(window));

	//Close OpenGL window and terminate GLFW  
	glfwDestroyWindow(window);
	//Finalize and clean up GLFW  
	glfwTerminate();

	exit(EXIT_SUCCESS);
}