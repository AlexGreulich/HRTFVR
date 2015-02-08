#ifndef HRTFVR_ENTITY_MANAGER_H
#define HRTFVR_ENTITY_MANAGER_H

#include "EntitySettings.h"
#include "Entity.h"
#include "Shader.h"
#include "Camera.h"
#include "Transform.h"
#include "Loader.h"
#include <vector>
#include <map>

class EntityFactory
{
public:
	EntityFactory(double* timer, Loader* loader);
	void SetupMaterials();

	void CreateEntity(const std::string name, glm::vec3 position);

	void Render(Shader* shader, Camera* camera);
	virtual ~EntityFactory();

protected:
private:

	double* m_timer;
	Loader* m_loader;
	std::vector<Entity*> m_entities;
	std::map<std::string, Material*> materials;
	EntitySettings m_entitySettings;
};



#endif