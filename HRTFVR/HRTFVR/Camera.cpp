#include "camera.h"

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar){
	m_pos = pos;
	m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_projection = glm::perspective(fov, aspect, zNear, zFar);
}

glm::mat4 Camera::GetViewProjection(){
	return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

void Camera::MoveForward(float amt)
{
	m_pos += m_forward * amt;
}

void Camera::MoveBack(float amt)
{
	m_pos -= m_forward * amt;
}

void Camera::MoveRight(float amt)
{
	m_pos -= glm::cross(m_up, m_forward) * amt;
}

void Camera::MoveLeft(float amt)
{
	m_pos += glm::cross(m_up, m_forward) * amt;
}

void Camera::Pitch(float angle)
{
	glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));

	m_forward = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(m_forward, 0.0)));
	m_up = glm::normalize(glm::cross(m_forward, right));
}

void Camera::RotateY(float angle)
{
	static const glm::vec3 UP(0.0f, 1.0f, 0.0f);

	glm::mat4 rotation = glm::rotate(angle, UP);

	m_forward = glm::vec3(glm::normalize(rotation * glm::vec4(m_forward, 0.0)));
	m_up = glm::vec3(glm::normalize(rotation * glm::vec4(m_up, 0.0)));
}

glm::vec3 Camera::GetForward(){
	return m_forward;
}