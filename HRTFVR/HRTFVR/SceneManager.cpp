#include "SceneManager.h"
#include <vector>

using namespace std;

/*
Load models, populate scene and update graph every frame
*/


vector<Entity> sceneObjects;

SceneManager::SceneManager()
{
	
}


SceneManager::~SceneManager()
{
}

void SceneManager::renderScene(){
	for (Entity e : sceneObjects){
		//render
	}
};