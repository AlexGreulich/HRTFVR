#ifndef HRTFVR_ENTITY_H
#define HRTFVR_ENTITY_H

#define GLM_FORCE_RADIANS
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "Texture.h"
#include "Mesh.h"
#include "Transform.h"


class Entity
{
public:
	
	// empty constructor for derived classes
	Entity();
	
	Entity(
		Texture* texture,
		Mesh* mesh,
		Material* mat,
		glm::vec3 position,
		double baseTimer
	);

	void Draw();
	void BindTexture();

	void SetPosition(glm::vec3 position);
	void SetTexture(Texture* texture);
	void SetMesh(Mesh* mesh);
	void SetMaterial(Material* material);
	void SetTimer(double timer);

	glm::vec3 GetPosition();
	Texture* GetTexture();
	Transform* GetTransform();
	Material* GetMaterial();
	Mesh* GetMesh();
	

	virtual ~Entity();
protected:
	Texture* m_texture;
	Mesh* m_mesh;
	Transform m_transform;
	std::string m_shader;
	
	double m_timer;
	Material* m_material;
};



#endif