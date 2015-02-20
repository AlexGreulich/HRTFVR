#ifndef HRTFVR_CAMERA_CPP
#define HRTFVR_CAMERA_CPP

#include "Camera.h"
#include <iostream>

Camera::Camera(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar){
	m_pos = pos;
	m_forward = glm::vec3(0.0f, 0.0f, -1.0f);
	m_up = glm::vec3(0.0f, 1.0f, 0.0f);
	m_projection = glm::perspective(fov, aspect, zNear, zFar);
}

glm::mat4 Camera::GetViewProjection(){
	return m_projection * glm::lookAt(m_pos, m_pos + m_forward, m_up);
}

glm::mat4 Camera::getView(){
	return glm::lookAt(m_pos, m_pos + m_forward, m_up); 
}

glm::mat4 Camera::getViewWithoutTranslation(){
	glm::mat4 view = glm::lookAt(m_pos, m_pos + m_forward, m_up);

	// reset translation
	view[3][0] = 0;
	view[3][1] = 0;
	view[3][2] = 0;

	return view;
}

glm::mat4 Camera::getProjection(){
	return m_projection;
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
void Camera::MoveUp(float amt)
{
	m_pos += m_up * amt;
}
void Camera::MoveDown(float amt)
{
	m_pos -= m_up * amt;
}
void Camera::Pitch(float angle)
{
	glm::vec3 right = glm::normalize(glm::cross(m_up, m_forward));

	glm::vec3 fwd = glm::vec3(glm::normalize(glm::rotate(angle, right) * glm::vec4(m_forward, 0.0)));

	// restrict camera to go upside-down
	if( m_up.y < 0 ){
		if(fwd.y > 0){
			fwd = glm::vec3(0, 1, 0);
		}else{
			fwd = glm::vec3(0, -1, 0);
		} 
	}

	glm::vec3 up = glm::normalize(glm::cross(m_forward, right));

	m_forward = fwd;
	m_up = up;
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

#endif