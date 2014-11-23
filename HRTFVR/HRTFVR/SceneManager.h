#pragma once


#include <GL/glew.h>  
#include <GLFW/glfw3.h>

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

//	vector<int> sceneObjects;

private:
	void renderScene();
};

