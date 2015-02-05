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
	Entity(Texture* texture, Mesh* mesh, Material* mat, glm::vec3 position, double baseTimer);
	void Draw();
	void BindTexture();
	void SetPosition(glm::vec3 position);
	void Rotate(glm::vec3 rotation);
	void StopRotate();
	glm::vec3 GetPosition();
	Transform* GetTransform();

	//void setMaterial(const Material& mat);
	Material* getMaterial();
	virtual ~Entity();
protected:
private:
	Texture* m_texture;
	Mesh* m_mesh;
	Transform m_transform;
	
	double m_timer;
	bool m_isRotating = false;
	glm::vec3 m_rotation_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	Material* m_material;
};



#endif