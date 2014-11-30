#include "Entity.h"


Entity::Entity(std::string texture, std::string mesh):
m_texture(texture),
m_mesh(mesh)
{
}

void Entity::Draw(){
	m_mesh.Draw();
}

void Entity::BindTexture(){
	m_texture.Bind();
}

Entity::~Entity()
{
}
