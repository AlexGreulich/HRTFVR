#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include "glm/ext.hpp"
#include <glm/gtx/transform.hpp>

struct Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	glm::mat4 GetViewProjection();
	glm::mat4 getView();
	glm::mat4 getProjection();
	glm::mat4 getViewWithoutTranslation();
	glm::vec3 GetForward();
	void MoveForward(float amt);
	void MoveBack(float amt);
	void MoveRight(float amt);
	void MoveLeft(float amt);
	void MoveUp(float amt);
	void MoveDown(float amt);

	void Pitch(float angle);
	void RotateY(float angle);

protected:
private:
	glm::mat4 m_projection;
	glm::vec3 m_pos;
	glm::vec3 m_forward;
	glm::vec3 m_up;
};

#endif