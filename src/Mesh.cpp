#ifndef HRTFVR_MESH_CPP
#define HRTFVR_MESH_CPP

#include "Mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>

Mesh::Mesh(){}

Mesh::Mesh(std::vector<GLfloat>& positions):
m_isSkybox(true)
{
	m_numIndices = positions.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glGenBuffers(1, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * positions.size(), &positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindVertexArray(0);
}

Mesh::Mesh(const std::string& fileName):
m_isSkybox(false)
{
	InitMesh(OBJModel(fileName).ToIndexedModel());
}

Mesh::Mesh(Geometry g, int t, float s):
m_isSkybox(false){
	InitMesh(g.toIndexedModel(t,s));
}

void Mesh::InitMesh(const IndexedModel& model)
{
	m_numIndices = model.indices.size();

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.positions[0]) * model.positions.size(), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.texCoords[0]) * model.texCoords.size(), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(model.indices[0]) * model.indices.size(), &model.indices[0], GL_STATIC_DRAW);

	glBindVertexArray(0);
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	if(m_isSkybox){
		glDrawArrays(GL_TRIANGLES, 0, (m_numIndices/3) );
	}else{
		glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0);
	}

	glBindVertexArray(0);	

}

Mesh::~Mesh()
{
	if( m_isSkybox ){
		glDeleteBuffers(1, 0);
	}else{
		glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);

	}
	glDeleteVertexArrays(1, &m_vertexArrayObject);
}


#endif