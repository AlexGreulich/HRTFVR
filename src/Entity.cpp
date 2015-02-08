#ifndef HRTFVR_ENTITY_CPP
#define HRTFVR_ENTITY_CPP

#include "Entity.h"
#include <math.h>
#include <ctime>
#include <iostream>

Entity::Entity(){}

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
	m_mesh->Draw();
}

void Entity::BindTexture(){
	m_texture->Bind();
}

void Entity::SetPosition(glm::vec3 pos){
	m_transform.SetPos(pos);
}

void Entity::SetTexture(Texture* texture){
	m_texture = texture;
}

void Entity::SetMesh(Mesh* mesh){
	m_mesh = mesh;
}

void Entity::SetMaterial(Material* material){
	m_material = material;
}

void Entity::SetTimer(double timer){
	m_timer = timer;
}


glm::vec3 Entity::GetPosition(){
	return m_transform.GetPos();
}

Transform* Entity::GetTransform(){
	return &m_transform;
}

Material* Entity::GetMaterial(){
	return this->m_material;
}

Texture* Entity::GetTexture(){
	return m_texture;
}

Mesh* Entity::GetMesh(){
	return m_mesh;
}

Entity::~Entity()
{}


#endif