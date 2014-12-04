#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"

struct Vertex
{
public:
	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

struct Material
{
public:
	Material(const glm::vec3& d, const glm::vec3& a, const glm::vec3& s, const glm::vec3& e, const float& sh)
	{
		diffuse = d;
		ambient = a;
		specular = s;
		emissive = e;
		shininess = sh;
	}

	glm::vec3 getDiffuse(){ return diffuse; }
	glm::vec3 getAmbient(){ return ambient; }
	glm::vec3 getSpecular(){ return specular;	}
	glm::vec3 getEmissive(){ return emissive;	}
	float getShininess(){ return shininess; }

private:
	glm::vec3 diffuse;
	glm::vec3 ambient;
	glm::vec3 specular;
	glm::vec3 emissive;
	float shininess;

};
enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};

class Mesh
{
public:
	Mesh(const std::string& fileName);
	void Draw();

	virtual ~Mesh();

protected:
private:
	static const unsigned int NUM_BUFFERS = 4;
	void InitMesh(const IndexedModel& model);

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;

};

#endif