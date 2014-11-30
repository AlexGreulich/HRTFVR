#pragma once
#include <string>
#include "texture.h"
#include "Mesh.h"

class Entity
{
public:
	Entity(std::string texture, std::string mesh);
	void Draw();
	void BindTexture();
	~Entity();
protected:
private:
	Texture m_texture;
	Mesh m_mesh;
	
};

