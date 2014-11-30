#include "EntityManager.h"
#include <iostream>

EntityManager::EntityManager():
m_entitySettings()
{
	CreateEntity("monkey");
}

void EntityManager::CreateEntity(const std::string name){

	EntitySettings::Setting setting = m_entitySettings.Get(name);
	if ( !setting ){
		std::cerr << "No setting found for: " << name << std::endl;
		return;
	}

	Entity* entity = new Entity(setting.texture, setting.mesh);

	m_entities.push_back( entity );

}

void EntityManager::Render(){
	for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
		(**it).BindTexture();
		(*it)->Draw();
	}
}

EntityManager::~EntityManager()
{
}
