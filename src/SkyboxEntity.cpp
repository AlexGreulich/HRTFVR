#ifndef HRTFVR_SKYBOX_ENTITY_CPP
#define HRTFVR_SKYBOX_ENTITY_CPP

#include "SkyboxEntity.h"

SkyboxEntity::SkyboxEntity()
{
	SetMesh(new Mesh(std::string("resources/meshes/skybox500.obj")));
	SetTexture( new CubeTexture("resources/textures/skybox_mir/") );
}

SkyboxEntity::SkyboxEntity(Mesh* mesh, CubeTexture* cubeTexture)
{
	SetMesh(mesh);
	SetTexture(cubeTexture);
}


void SkyboxEntity::Draw(){
	glFrontFace( GL_CW );
	m_mesh->Draw();
	glFrontFace( GL_CCW );
}

SkyboxEntity::~SkyboxEntity(){
	
}

#endif