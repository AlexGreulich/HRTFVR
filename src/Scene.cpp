#ifndef HRTFVR_SCENE_CPP
#define HRTFVR_SCENE_CPP

#include "Scene.h"

Scene::Scene(Loader* loader, Camera* camera, double* timer):
m_loader(loader),
m_camera(camera),
m_timer(timer),
m_light(new Light(glm::vec3(1000, 1000, -1000), glm::vec3(-1, -1, 1))),
m_skybox(new SkyboxEntity())
{

	ShaderFactory::GetInstance().CreateShader(
		"basic",
		"resources/shaders/basic.vertex",
		"resources/shaders/basic.fragment"
	);

	ShaderFactory::GetInstance().CreateShader(
		"skybox",
		"resources/shaders/skybox.vertex",
		"resources/shaders/skybox.fragment"
	);

	std::vector<Texture*> mtex;
	mtex.push_back(m_loader->GetTexture("resources/textures/Grass0129_9_S.jpg"));
	mtex.push_back(m_loader->GetTexture("resources/textures/SoilMud0091_5_S.jpg"));

	Entity* terrain = new Entity(
		mtex,
		m_loader->GetMesh("resources/meshes/terrain_mud.obj"),
		m_loader->GetMaterial("resources/materials/terrain_mud.mtl"),
		glm::vec3(0, -40, 0),
		*m_timer
	);

	Entity* monkey = new Entity(
		m_loader->GetTexture("resources/textures/cube-texture.bmp"),
		m_loader->GetMesh("resources/meshes/monkey.obj"),
		m_loader->GetMaterial("resources/materials/bronze.mtl"),
		glm::vec3(100, 100, -100),
		*m_timer
	);

	m_entities.push_back(terrain);
	m_entities.push_back(monkey);
}

void Scene::Render(){

	Shader* basicShader = ShaderFactory::GetInstance().GetShader("basic");
	Shader* skyboxShader = ShaderFactory::GetInstance().GetShader("skybox");

	skyboxShader->Bind();
	m_skybox->GetTexture()->Bind();
	skyboxShader->UpdateMVP(
		m_skybox->GetTransform()->GetModel(),
		m_camera->getView(),
		m_camera->getProjection()
	);
	m_skybox->Draw();
	basicShader->Bind();

	for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
		
		(*it)->BindTexture(basicShader); 
		glBindTexture(GL_TEXTURE_2D, 0);

		basicShader->Update(
			(*it)->GetTransform(),
			m_camera,
			(*it)->GetMaterial()
		);

		basicShader->UpdateLight(m_light);

		(*it)->Draw();
		glBindTexture(GL_TEXTURE_2D, 0);

	}
}

Scene::~Scene(){
	
}

#endif