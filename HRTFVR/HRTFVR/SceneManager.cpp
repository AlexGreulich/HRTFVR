#include "SceneManager.h"
#include <vector>

using namespace std;

/*
Load models, populate scene and update graph every frame
*/


vector<Entity> sceneObjects;

SceneManager::SceneManager()
{
	objLoader = new ObjLoader();
}

void SceneManager::loadObjFiles(){
	objLoader->processFiles();
}

SceneManager::~SceneManager()
{
}

void SceneManager::renderScene(){
	for (Entity e : sceneObjects){
		//render
	}
};