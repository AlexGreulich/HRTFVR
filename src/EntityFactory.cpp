#ifndef HRTFVR_ENTITY_MANAGER_CPP
#define HRTFVR_ENTITY_MANAGER_CPP

#include "EntityFactory.h"
#include <iostream>
#include "Logger.h"

EntityFactory::EntityFactory(double* timer, Loader* loader):
m_loader(loader),
m_entitySettings(),
m_timer(timer)
{
	SetupMaterials();
	CreateEntity("terrain_mud", glm::vec3(0, -4.0f, 0));
}

void EntityFactory::CreateEntity(const std::string name, glm::vec3 position){

	EntitySettings::Setting setting = m_entitySettings.Get(name);
	
	// check if setting exists
	if (!setting){
		LOG(FATAL) << "No setting found for: " << name;
		return;
	}
	
	// check if mesh & texture is loaded yet...
	if ( false == m_loader->MeshExists(setting.mesh) || false == m_loader->TextureExists(setting.texture) ){
		LOG(FATAL) << "Mesh " << setting.mesh << " or texture " << setting.texture << " is not loaded";
		return;
	}

	// finally create entity
	Entity* entity = new Entity(
		m_loader->GetTexture(setting.texture),
		m_loader->GetMesh(setting.mesh),
		materials[name],
		position,
		*m_timer
	);

	m_entities.push_back(entity);

}

void EntityFactory::Render(Shader* shader, Camera* camera){
	for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
		
		shader->Update(
			(*it)->GetTransform(),
			camera,
			(*it)->GetMaterial()
		);

		(*it)->BindTexture();
		(*it)->Draw();
	}
}

void EntityFactory::SetupMaterials(){

	materials["cube"] = new Material(glm::vec4(0.5f), glm::vec4(0.2f), glm::vec4(0.7f), glm::vec4(0.1f), 5.0f);
	materials["monkey"] = 
		new Material(		// its going to be a jade monkey
			glm::vec4(0.54f, 0.89f, 0.63f, 1.0f), //diffuse
			glm::vec4(0.14f, 0.22f, 0.16f, 1.0f), // ambient
			glm::vec4(0.32f, 0.32f, 0.32f, 1.0f),  // specular
			glm::vec4(0.0f), // emmissive
			12.8f // shininess
		);
	materials["skyscraper"] = new Material(glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), 0.0f);
	materials["octahedron"] = new Material(glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), glm::vec4(0.0f), 0.0f);
	materials["teapot"] = 
		new Material(	//polished bronze pot
			glm::vec4(0.4f, 0.24f, 0.1f, 1.0f),
			glm::vec4(0.25f, 0.15f, 0.06f, 1.0f),
			glm::vec4(0.77f, 0.46f, 0.20f, 1.0f),
			glm::vec4(0.0f),
				76.8f
		);

	materials["terrain_mud"] = 
		new Material(	//polished bronze
			glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
			glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(1.0f),
			20.0f
		);

}

EntityFactory::~EntityFactory()
{
	//
	//  MATERIALS
	//
	for( std::map<std::string, Material*>::iterator it = materials.begin(); it != materials.end(); ++it ){
		delete (*it).second;
	}

	//
	//  ENTITIES
	//
	for (unsigned int i = 0; i < m_entities.size(); i++){
		
		delete m_entities[i];
	}

}


#endif