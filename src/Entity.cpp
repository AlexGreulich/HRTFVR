#ifndef HRTFVR_ENTITY_CPP
#define HRTFVR_ENTITY_CPP

#include "Entity.h"
#include <math.h>
#include <ctime>
#include <iostream>

Entity::Entity(Texture* texture, Mesh* mesh, Material* mat, glm::vec3 position, double baseTimer):
m_texture(texture),
m_mesh(mesh),
m_material(mat),
m_timer(baseTimer),
m_transform()
{
	m_transform.SetPos(position);
}

void Entity::Draw(){

	if ( m_isRotating ){
		double ctime = glfwGetTime() - m_timer;
		glm::vec3 timedVector(ctime * m_rotation_speed.x, ctime * m_rotation_speed.y, ctime * m_rotation_speed.z);
		m_transform.SetRot(timedVector * m_rotation_speed);
	}
	m_mesh->Draw();
}

void Entity::BindTexture(){
	m_texture->Bind();
}

void Entity::Rotate(glm::vec3 rotation){
	m_rotation_speed = rotation;
	m_isRotating = true;
}

void Entity::StopRotate(){
	m_isRotating = false;
}

void Entity::SetPosition(glm::vec3 pos){
	m_transform.SetPos(pos);
}

glm::vec3 Entity::GetPosition(){
	return m_transform.GetPos();
}

Transform* Entity::GetTransform(){
	return &m_transform;
}

Material* Entity::getMaterial(){
	return this->m_material;
}

Entity::~Entity()
{}


#endif