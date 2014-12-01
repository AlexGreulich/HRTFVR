#pragma once
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include "texture.h"
#include "Mesh.h"
#include "transform.h"


class Entity
{
public:
	Entity(Texture* texture, Mesh* mesh, glm::vec3 position, double baseTimer);
	void Draw();
	void BindTexture();
	void SetPosition(glm::vec3 position);
	void Rotate(glm::vec3 rotation);
	void StopRotate();
	glm::vec3 GetPosition();
	Transform* GetTransform();
	~Entity();
protected:
private:
	Texture* m_texture;
	Mesh* m_mesh;
	Transform m_transform;
	double m_timer;
	bool m_isRotating = false;
	glm::vec3 m_rotation_speed = glm::vec3(0.0f, 0.0f, 0.0f);
	
};

