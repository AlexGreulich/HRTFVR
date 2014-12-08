#ifndef TRANSFORM_INCLUDED_H
#define TRANSFORM_INCLUDED_H

#include <glm.hpp>
#include <gtx/transform.hpp>
#include "camera.h"

struct Transform
{
public:
	Transform(const glm::vec3 pos = glm::vec3(), const glm::vec3 rot = glm::vec3(), const glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f));

	glm::mat4 GetModel();
	glm::mat4 GetMVP(Camera *camera);
	glm::mat4 getNormalMat(Camera *camera);

	glm::vec3 GetPos();
	glm::vec3 GetRot();
	glm::vec3 GetScale();

	void SetPos(glm::vec3 pos);
	void SetRot(glm::vec3 rot);
	void SetScale(glm::vec3 scale);
protected:
private:
	glm::vec3 m_pos;
	glm::vec3 m_rot;
	glm::vec3 m_scale;
};

#endif