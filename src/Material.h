#ifndef HRTFVR_MATERIAL_H
#define HRTFVR_MATERIAL_H


struct Material
{
public:
	Material(const glm::vec4& d, const glm::vec4& a, const glm::vec4& s, const glm::vec4& e, const float& sh)
	{
		diffuse = d;
		ambient = a;
		specular = s;
		emissive = e;
		shininess = sh;
	}

	glm::vec4 getDiffuse(){ return diffuse; }
	glm::vec4 getAmbient(){ return ambient; }
	glm::vec4 getSpecular(){ return specular;	}
	glm::vec4 getEmissive(){ return emissive;	}
	
	float getShininess(){ return shininess; }

private:
	glm::vec4 diffuse;
	glm::vec4 ambient;
	glm::vec4 specular;
	glm::vec4 emissive;
	float shininess;

};

#endif