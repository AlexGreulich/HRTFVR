#ifndef MESH_INCLUDED_H
#define MESH_INCLUDED_H

#define GLM_FORCE_RADIANS
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <vector>
#include "obj_loader.h"
#include "Material.h"

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
	Mesh();
	Mesh(std::vector<GLfloat>& positions);
	Mesh(const std::string& fileName);
	void Draw();

	virtual ~Mesh();

protected:
	static const unsigned int NUM_BUFFERS = 4;
	void InitMesh(const IndexedModel& model);

	bool m_isSkybox;
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_numIndices;

};

#endif
