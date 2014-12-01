#include "Entity.h"
#include <math.h>


Entity::Entity(Texture* texture, Mesh* mesh, glm::vec3 position, double* timer):
m_transform()
{
	m_texture = texture;
	m_mesh = mesh;
	m_timer = timer;
	m_transform.SetPos(position);
}

void Entity::Draw(){

	if ( m_isRotating ){
		glm::vec3 timeVector(*m_timer * m_rotation_speed.x, *m_timer * m_rotation_speed.y, *m_timer * m_rotation_speed.z);
		m_transform.SetRot(timeVector * m_rotation_speed);
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

Entity::~Entity()
{
}
