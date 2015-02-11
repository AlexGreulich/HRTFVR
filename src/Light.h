#ifndef HRTFVR_LIGHT_H
#define HRTFVR_LIGHT_H

#include <GL/glew.h>
#include <glm/glm.hpp>

class Light{
public:
	Light(glm::vec3 position, glm::vec3 color){
		m_position = position;
		m_color = color;
	}

	void SetPosition(glm::vec3 pos){ m_position = pos; }
	void SetColor(glm::vec3 color){ m_color = color; }

	glm::vec3 GetPosition(){ return m_position; }
	glm::vec3 GetColor(){ return m_color; }

protected:
	glm::vec3 m_position;
	glm::vec3 m_color;
};

#endif