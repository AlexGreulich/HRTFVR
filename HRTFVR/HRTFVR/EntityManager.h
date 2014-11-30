#pragma once
#include "EntitySettings.h"
#include "Entity.h"
#include <vector>

class EntityManager
{
public:
	EntityManager();
	void CreateEntity(const std::string name);
	void Render();
	virtual ~EntityManager();

protected:
private:
	
	std::vector<Entity*> m_entities;
	EntitySettings m_entitySettings;
};

