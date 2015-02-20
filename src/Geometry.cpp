#include "Geometry.h"


Geometry::Geometry(int platonicType)
{
	ps = PlatonicSolid(platonicType);
}

IndexedModel Geometry::toIndexedModel(int tess, float scale)
{
	IndexedModel m;
	
	m.positions = ps.getVertexData();
	m.indices = ps.getConnectivity();

	if (tess > 0) { m = tesselateMesh(tess, m); }	

	if (scale != 1.0f){
		for (unsigned int i = 0; i < m.positions.size(); i++){
			m.positions.at(i) *= scale;
		}
	}

	// set texture data TODO
	float u = 0.5f;
	float v = 0.5f;
	
	for (unsigned int iTex = 0; iTex < m.positions.size(); iTex++){
		m.texCoords.push_back(glm::vec2(u, v));
	}

	
	//calculate final normals
	m.normals;	
	for (unsigned int i = 0; i < m.indices.size(); i += 3)
	{
		int i0 = m.indices[i];
		int i1 = m.indices[i + 1];
		int i2 = m.indices[i + 2];

		glm::vec3 v1 = m.positions[i1] - m.positions[i0];
		glm::vec3 v2 = m.positions[i2] - m.positions[i0];

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		m.normals.push_back(normal);
		m.normals.push_back(normal);
		m.normals.push_back(normal);
	}

	for (unsigned int i = 0; i < m.normals.size(); i++){
		m.normals[i] = glm::normalize(m.normals[i]);
	}

	

	return m;
}

IndexedModel Geometry::tesselateMesh(int t, IndexedModel m)
{
	std::vector<glm::vec3> newPositions;
	std::vector<unsigned int> newIndices;

	std::vector<glm::vec3>::iterator it;

	for (unsigned int i = 0; i < ps.getConnectivity().size(); i+=3){

		glm::vec3 a = ps.getVertexData().at(ps.getConnectivity().at(i));
		glm::vec3 b = ps.getVertexData().at(ps.getConnectivity().at(i + 1));
		glm::vec3 c = ps.getVertexData().at(ps.getConnectivity().at(i + 2));

		glm::vec3 ab = (b - a) / 2.0f;
		glm::vec3 ac = (c - a) / 2.0f;
		glm::vec3 bc = (c - b) / 2.0f;

		//newPositions.push_back(a);
		//newPositions.push_back(b);
		//newPositions.push_back(c);

		//newPositions.push_back(ab);
		//newPositions.push_back(bc);
		//newPositions.push_back(ac);

		//add 3 new vertices to vertex array
		m.positions.push_back(ab);
		m.positions.push_back(bc);
		m.positions.push_back(ac);
		
		// get index of new vertices
		it = find(m.positions.begin(), m.positions.end(), ab);
		unsigned int iab = std::distance(m.positions.begin(), it);

		it = find(m.positions.begin(), m.positions.end(), ac);
		unsigned int iac = std::distance(m.positions.begin(), it);

		it = find(m.positions.begin(), m.positions.end(), bc);
		unsigned int ibc = std::distance(m.positions.begin(), it);

		//replace face with 4 new ones
		newIndices.push_back(i);
		newIndices.push_back(iab);
		newIndices.push_back(iac);

		newIndices.push_back(i + 1);
		newIndices.push_back(ibc);
		newIndices.push_back(iab);
		
		newIndices.push_back(i + 2);
		newIndices.push_back(iac);
		newIndices.push_back(ibc);

		newIndices.push_back(iab);
		newIndices.push_back(ibc);
		newIndices.push_back(iac);

		/*
		newIndices.push_back(0 + i);
		newIndices.push_back(3 + i);
		newIndices.push_back(5 + i);

		newIndices.push_back(3 + i);
		newIndices.push_back(1 + i);
		newIndices.push_back(4 + i);

		newIndices.push_back(3 + i);
		newIndices.push_back(4 + i);
		newIndices.push_back(5 + i);

		newIndices.push_back(5 + i);
		newIndices.push_back(4 + i);
		newIndices.push_back(2 + i);
		*/
	}

	for (int i = 0; i < m.positions.size(); i++){
		m.positions.at(i) = glm::normalize(m.positions.at(i));
	}

	//m.positions = newPositions;
	m.indices = newIndices;

	return m;
}

Geometry::~Geometry()
{
}
