#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

class Display
{
public:
	Display(int width, int height, std::string title);
	void Update();
	void Clear(float r, float g, float b, float a);
	int getKey();
	GLFWwindow* getWindow();
	int getWidth();
	int getHeight();
	virtual ~Display();
protected:
private:
	void setupOpenGL();
	GLFWwindow *m_window;
	int m_width;
	int m_height;
};

