#ifndef CAMERA_INCLUDED_H
#define CAMERA_INCLUDED_H

#include <glm.hpp>
#include <gtx/transform.hpp>

struct Camera
{
public:
	Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);

	glm::mat4 GetViewProjection();

	void MoveForward(float amt);
	void MoveBack(float amt);
	void MoveRight(float amt);
	void MoveLeft(float amt);

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