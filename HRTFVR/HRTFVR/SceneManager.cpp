#include "SceneManager.h"
#include <vector>
#include "Entity.h"
using namespace std;

/*
Load models, populate scene and update graph every frame
*/


vector<Entity*> sceneObjects;

SceneManager::SceneManager()
{
	
	Entity *e = new Entity();
	sceneObjects.push_back(e);
}


SceneManager::~SceneManager()
{
}

void SceneManager::renderScene(){
	for (Entity *e : sceneObjects){
		
	}
};