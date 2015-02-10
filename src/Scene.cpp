#ifndef HRTFVR_SCENE_CPP
#define HRTFVR_SCENE_CPP

#include "Scene.h"

Scene::Scene(Loader* loader, Camera* camera, double* timer):
m_loader(loader),
m_camera(camera),
m_timer(timer),
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

	Entity* terrain = new Entity(
		m_loader->GetTexture("resources/textures/SoilMud0091_5_S.jpg"),
		m_loader->GetMesh("resources/meshes/terrain_mud.obj"),
		new Material(
			glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
			glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),
			glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
			glm::vec4(1.0f),
			20.0f
		),
		glm::vec3(0, -4, 0),
		*m_timer
	);

	m_entities.push_back(terrain);
}

void Scene::Render(){

	Shader* basicShader = ShaderFactory::GetInstance().GetShader("basic");
	Shader* skyboxShader = ShaderFactory::GetInstance().GetShader("skybox");

	skyboxShader->Bind();

	m_skybox->GetTexture()->Bind();

	skyboxShader->Update(
		m_skybox->GetTransform()->GetModel(),
		m_camera->getView(),
		m_camera->getProjection()
	);

	m_skybox->Draw();

	basicShader->Bind();

	for (std::vector<Entity*>::iterator it = m_entities.begin(); it != m_entities.end(); ++it){
		
		(*it)->GetTexture()->Bind();

		basicShader->Update(
			(*it)->GetTransform(),
			m_camera,
			(*it)->GetMaterial()
		);


		(*it)->Draw();
	}
}

Scene::~Scene(){
	
}

#endif