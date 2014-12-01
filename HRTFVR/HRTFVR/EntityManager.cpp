#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager(double* timer):
m_entitySettings()
{
	// store pointer to timer
	m_timer = timer;

	SetupMeshes();
	SetupTextures();
	
	CreateEntity("teapot", glm::vec3(0.0f, 0.0f, 0.0f));
}

void EntityManager::SetupMeshes(){

	//@todo place this in header if possible
	std::string m_meshPreloader[2] = {
		"./res/meshes/monkey.obj",
		"./res/meshes/tpt.obj"
	};

	// for every string in preloader:
	// load it into the mesh map
	// and make it available with the path as key
	for (std::string* p = &m_meshPreloader[0]; p != &m_meshPreloader[2]; ++p){
		m_meshMap[*p] = new Mesh(*p);
	}

}

void EntityManager::SetupTextures(){
	
	//@todo place this in header if possible
	std::string m_texturePreloader[1] = {
		"./res/textures/bricks.jpg"
	};

	// for every string in preloader:
	// load it into the mesh map
	// and make it available with the path as key
	for (std::string* p = &m_texturePreloader[0]; p != &m_texturePreloader[1]; ++p){
		m_textureMap[*p] = new Texture(*p);
	}

}

void EntityManager::CreateEntity(const std::string name, glm::vec3 position, bool rotate){

	EntitySettings::Setting setting = m_entitySettings.Get(name);
	
	// check if setting exists
	if (!setting){
		std::cerr << "No setting found for: " << name << std::endl;
		return;
	}
	
	// check if mesh & texture is loaded yet...
	if ( m_meshMap.find(setting.mesh) == m_meshMap.end() || m_textureMap.find(setting.texture) == m_textureMap.end() ){
		std::cout << "mesh " << setting.mesh << " or texture " << setting.texture << " not loaded" << std::endl;
		return;
	}

	// finalyl create entity
	Entity* entity = new Entity(m_textureMap.at(setting.texture), m_meshMap.at(setting.mesh), position, m_timer);

	if (rotate){
		entity->Rotate(glm::vec3(10.0f, 5.0f, 0.0f));
	}

	m_entities.push_back(entity);

}

void EntityManager::CreateEntity(const std::string name, glm::vec3 position){
	
	CreateEntity(name, position, false);

}

void EntityManager::Render(Shader* shader, Camera* camera){
	for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
		
		shader->Update((*it)->GetTransform(), camera);
		(**it).BindTexture();
		(*it)->Draw();
	}
}

EntityManager::~EntityManager()
{
}
