#include "transform.h"
#include <glm.hpp>

Transform::Transform(const glm::vec3 pos, const glm::vec3 rot, const glm::vec3 scale){
	m_pos = pos;
	m_rot = rot;
	m_scale = scale;
}

glm::mat4 Transform::GetModel()
{
	glm::mat4 posMat = glm::translate(m_pos);
	glm::mat4 scaleMat = glm::scale(m_scale);
	glm::mat4 rotX = glm::rotate(m_rot.x, glm::vec3(1.0, 0.0, 0.0));
	glm::mat4 rotY = glm::rotate(m_rot.y, glm::vec3(0.0, 1.0, 0.0));
	glm::mat4 rotZ = glm::rotate(m_rot.z, glm::vec3(0.0, 0.0, 1.0));
	glm::mat4 rotMat = rotX * rotY * rotZ;

	return posMat * rotMat * scaleMat;
}

glm::mat4 Transform::GetMVP(Camera *camera)
{
	glm::mat4 VP = camera->GetViewProjection();
	glm::mat4 M = GetModel();

	return VP * M;//camera.GetViewProjection() * GetModel();
}

glm::vec3 Transform::GetPos(){
	return m_pos;
}

glm::vec3 Transform::GetRot(){
	return m_rot;
}

glm::vec3 Transform::GetScale(){
	return m_scale;
}

void Transform::SetPos(glm::vec3 pos){
	m_pos = pos;
}

void Transform::SetRot(glm::vec3 rot){
	m_rot = rot;
}

void Transform::SetScale(glm::vec3 scale){
	m_scale = scale;
}
