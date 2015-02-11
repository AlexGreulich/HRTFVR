#ifndef HRTFVR_SCENE_H
#define HRTFVR_SCENE_H

#include "Logger.h"
#include "Terrain.h"
#include "Loader.h"
#include "Entity.h"
#include "Material.h"
#include "Camera.h"
#include "Light.h"
#include "SkyboxEntity.h"
#include "ShaderFactory.h"
#include <vector>

class Scene{

public:
	Scene(Loader* loader, Camera* camera, double* timer);
	void Render();
	virtual ~Scene();

protected:
	double* m_timer;
	Loader* m_loader;
	Camera* m_camera;
	Light* m_light;
	std::vector<Entity*> m_entities;
	SkyboxEntity* m_skybox;
};

#endif