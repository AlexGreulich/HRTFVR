#ifndef HRTFVR_ENTITY_CPP
#define HRTFVR_ENTITY_CPP

#include "Entity.h"
#include <math.h>
#include <ctime>
#include <iostream>

Entity::Entity(){}

/**
 * TEX / MESH / MAT / POS / TIMER
 */
Entity::Entity(Texture* texture, Mesh* mesh, Material* mat, glm::vec3 position, double baseTimer):
m_texture(texture),
m_mesh(mesh),
m_material(mat),
m_timer(baseTimer),
m_transform()
{
	m_textures.push_back(texture);
	m_transform.SetPos(position);
}

/**
 * [VEC]TEXTURES / MESH / MAT / POS / TIMER
 */
Entity::Entity(
	std::vector<Texture*> textures,
	Mesh* mesh,
	Material* mat,
	glm::vec3 position,
	double baseTimer):
m_mesh(mesh),
m_material(mat),
m_timer(baseTimer),
m_transform()
{
	m_textures = textures;
	m_transform.SetPos(position);
}

/**
 * MESH / MAT / POS / TIMER
 */
Entity::Entity(Mesh* mesh, Material* mat, glm::vec3 position, double baseTimer):
m_texture(new Texture()),
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

void Entity::BindTexture(Shader* shader){

	for( std::vector<Entity*>::size_type i = 0; i < m_textures.size(); i++ ){
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, m_textures[i]->GetId());		
		shader->UpdateTextureSampler( Shader::UNIFORM_TEX_SAMPLER_0 + i, i );
	}

}

void Entity::UnbindTexture(){

	for( std::vector<Entity*>::size_type i = 0; i < m_textures.size(); i++ ){
		glActiveTexture(GL_TEXTURE0+i);
		glBindTexture(GL_TEXTURE_2D, 0);		
	}

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
	return m_material;
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