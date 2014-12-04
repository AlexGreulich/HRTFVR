#pragma once
#include "EntitySettings.h"
#include "Entity.h"
#include "Shader.h"
#include "camera.h"
#include "transform.h"
#include <vector>
#include <map>

class EntityManager
{
public:
	EntityManager(double* timer);
	void SetupMeshes();
	void SetupTextures();
	void setupMaterials();

	void CreateEntity(const std::string name, glm::vec3 position, bool rotate);
	void CreateEntity(const std::string name, glm::vec3 position);

	void Render(Shader* shader, Camera* camera);
	virtual ~EntityManager();

protected:
private:

	double* m_timer;
	std::vector<Entity*> m_entities;
	std::map<std::string, Mesh*> m_meshMap;
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, Material*> materials;

	EntitySettings m_entitySettings;
};

