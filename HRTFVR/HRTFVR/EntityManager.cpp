#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager(double* timer):
m_entitySettings()
{
	// store pointer to timer
	m_timer = timer;

	SetupMeshes();
	SetupTextures();
	setupMaterials();
	CreateEntity("teapot", glm::vec3(10.0f, 0.0f, 5.0f));
	CreateEntity("monkey", glm::vec3(10.0f, 0.0f, -5.0f));
	
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
	Entity* entity = new Entity(m_textureMap.at(setting.texture), m_meshMap.at(setting.mesh), materials[name], position, *m_timer);

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
		
		shader->Update((*it)->GetTransform(), camera, (*it)->getMaterial());
		(**it).BindTexture();
		(*it)->Draw();
	}
}

void EntityManager::setupMaterials(){
	materials["cube"] = new Material(glm::vec4(0.5f), glm::vec4(0.2f), glm::vec4(0.7f), glm::vec4(0.1f), 5.0f);
	materials["monkey"] = 
		new Material(		// its going to be a jade monkey
			glm::vec4(0.54f, 0.89f, 0.63f, 1.0f), //diffuse
			glm::vec4(0.14f, 0.22f, 0.16f, 1.0f),
			glm::vec4(0.32f, 0.32f, 0.32f, 1.0f),
			glm::vec4(0.0f),
			12.8f);
	materials["skyscraper"] = new Material(glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), 0.0f);
	materials["octahedron"] = new Material(glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), 0.0f);
	materials["teapot"] = 
		new Material(	//polished bronze pot
		glm::vec4(0.4f, 0.24f, 0.1f, 1.0f),
		glm::vec4(0.25f, 0.15f, 0.06f, 1.0f),
		glm::vec4(0.77f, 0.46f, 0.20f, 1.0f),
		glm::vec4(0.0f),
			76.8f);

}

EntityManager::~EntityManager()
{
	// Stuff has to be deleted!!! There is an error when closing the application
	//for (int i = 0; i < m_entities.size(); i++){
		
	//	m_entities[i]->~Entity();
	//}
	m_entities.clear();
	m_textureMap.clear();
	m_meshMap.clear();
	materials.clear();

}
