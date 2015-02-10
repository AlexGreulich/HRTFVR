#ifndef HRTFVR_SKYBOX_ENTITY_CPP
#define HRTFVR_SKYBOX_ENTITY_CPP

#include "SkyboxEntity.h"

SkyboxEntity::SkyboxEntity()
{

	m_mesh = new Mesh(std::string("resources/meshes/skybox500.obj"));

	SetTexture( new CubeTexture("resources/textures/skybox/") );

	SetMaterial(new Material(
		glm::vec4(0.2f, 0.2f, 0.2f, 1.0f),
		glm::vec4(0.8f, 0.8f, 0.8f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f),
		20.0f
	));

}

void SkyboxEntity::Draw(){
	glFrontFace( GL_CW );
	m_mesh->Draw();
	glFrontFace( GL_CCW );
}

SkyboxEntity::~SkyboxEntity(){
	
}

#endif