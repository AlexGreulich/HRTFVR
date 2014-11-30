#include "Display.h"
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

Display::Display(int width, int height, std::string title)
{
	m_width = width;
	m_height = height;

	if (!glfwInit())
		std::cerr << "could not initialize GLFW" << std::endl;

	m_window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	
	if (!m_window)
		glfwSetWindowShouldClose(m_window, 1);

	glfwMakeContextCurrent(m_window);
	
	glewExperimental = GL_TRUE;
	GLenum error = glGetError();

	if (!error != GL_NO_ERROR){
		std::cerr << "OpenGL Error: " << error << std::endl;
	}

	GLenum glewinit = glewInit();

	if ( glewinit != GLEW_OK ){
		std::cerr << "Glew not okay! " << glewinit;
	}

	glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	setupOpenGL();

}

void Display::setupOpenGL(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glCullFace(GL_BACK);

	glClearColor(0.0f, 0.15f, 0.3f, 1.0f);
}

void Display::Clear(float r, float g, float b, float a){
	glClearColor(r, g, b, a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Display::Update(){
	
	glfwSwapBuffers(m_window);
	glfwPollEvents();
}

int Display::getWidth(){
	return m_width;
}

int Display::getHeight(){
	return m_height;
}

GLFWwindow* Display::getWindow(){
	return m_window;
}


Display::~Display()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}
