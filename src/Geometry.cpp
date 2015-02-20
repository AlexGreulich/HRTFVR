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

	if (tess > 0) { 
		for (int t = 0; t < tess; t++){
			m = tesselateMesh(m); 
		}		
	}	

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
		int i0 = m.indices.at(i);
		int i1 = m.indices.at(i + 1);
		int i2 = m.indices.at(i + 2);

		glm::vec3 v1 = m.positions.at(i1) - m.positions.at(i0);
		glm::vec3 v2 = m.positions.at(i2) - m.positions.at(i0);

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		m.normals.push_back(normal);
		m.normals.push_back(normal);
		m.normals.push_back(normal);
	}

	for (unsigned int i = 0; i < m.normals.size(); i++){
		m.normals.at(i) = glm::normalize(m.normals.at(i));
	}	

	return m;
}

IndexedModel Geometry::tesselateMesh(IndexedModel m)
{
	std::vector<unsigned int> newIndices;

	for (unsigned int i = 0; i < m.indices.size(); i+=3){
		glm::vec3 a = m.positions.at(m.indices.at(i));
		glm::vec3 b = m.positions.at(m.indices.at(i + 1));
		glm::vec3 c = m.positions.at(m.indices.at(i + 2));

		glm::vec3 ab = (b + a) / 2.0f;
		glm::vec3 ac = (c + a) / 2.0f;
		glm::vec3 bc = (c + b) / 2.0f;

		//add 3 new vertices to vertex array
		m.positions.push_back(ab);
		m.positions.push_back(bc);
		m.positions.push_back(ac);
		
		// get index of new vertices
		unsigned int iab = find(m.positions.begin(), m.positions.end(), ab) - m.positions.begin();
		unsigned int iac = find(m.positions.begin(), m.positions.end(), ac) - m.positions.begin();
		unsigned int ibc = find(m.positions.begin(), m.positions.end(), bc) - m.positions.begin();
		
		//replace face with 4 new ones
		newIndices.push_back(m.indices.at(i));
		newIndices.push_back(iab);
		newIndices.push_back(iac);

		newIndices.push_back(m.indices.at(i+ 1));
		newIndices.push_back(ibc);
		newIndices.push_back(iab);
		
		newIndices.push_back(m.indices.at(i + 2));
		newIndices.push_back(iac);
		newIndices.push_back(ibc);

		newIndices.push_back(iab);
		newIndices.push_back(ibc);
		newIndices.push_back(iac);
	}

	for (unsigned int i = 0; i < m.positions.size(); i++){
		m.positions.at(i) = glm::normalize(m.positions.at(i));
	}

	m.indices = newIndices;

	return m;
}

Geometry::~Geometry()
{
}
