#ifndef HRTFVR_MATERIAL_H
#define HRTFVR_MATERIAL_H

#include <string>

class Material
{
public:

	Material() {}

	Material(const glm::vec4& d, const glm::vec4& a, const glm::vec4& s, const glm::vec4& e, const float& sh)
	{
		diffuse = d;
		ambient = a;
		specular = s;
		emissive = e;
		shininess = sh;
	}

	/**
	 * setter
	 */
	glm::vec4 getDiffuse(){ return diffuse; }
	glm::vec4 getAmbient(){ return ambient; }
	glm::vec4 getSpecular(){ return specular; }
	glm::vec4 getEmissive(){ return emissive; }
	std::string getName(){ return m_name; }
	float getDensity(){ return m_density; }

	/**
	 * getter
	 */
	void SetDiffuse(glm::vec4 d){ diffuse = d; }
	void SetAmbient(glm::vec4 a){ ambient = a; }
	void SetSpecular(glm::vec4 s){ specular = s; }
	void SetEmissive(glm::vec4 e){ emissive = e; }
	void SetName(std::string name){ m_name = name; }
	void SetDensity(float density){ m_density = density; }
	void SetShiny(float s){ shininess = s; }
	
	float getShininess(){ return shininess; }

private:
	glm::vec4 diffuse;
	glm::vec4 ambient;
	glm::vec4 specular;
	glm::vec4 emissive;
	float shininess;
	float m_density;
	std::string m_name;

};

#endif