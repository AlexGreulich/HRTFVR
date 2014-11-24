#pragma once



#include "Entity.h"
#include "ObjLoader.h"

class SceneManager
{
public:
	SceneManager();
	void loadObjFiles();
	~SceneManager();

//	vector<int> sceneObjects;

private:
	void renderScene();
	ObjLoader *objLoader;
};

