#include <stdlib.h>
#include <glm/gtc/constants.hpp>

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

	// set texture data TODO
	m.texCoords = std::vector<glm::vec2>(m.indices.size(), glm::vec2(0.0f, 0.0f));
	for (int i = 0; i < m.indices.size(); i += 3){
		//for (int j = 0; j < 3; j++){
		glm::vec3 p1 = glm::normalize(m.positions.at(m.indices.at(i)));
		glm::vec3 p2 = glm::normalize(m.positions.at(m.indices.at(i + 1)));
		glm::vec3 p3 = glm::normalize(m.positions.at(m.indices.at(i + 2)));

		if (m.texCoords.at(i) == glm::vec2(0.0f, 0.0f)){
			/*
			Spherical texture mapping is no trivial task at all and not possible without distortion
			i found this, seems fairly simple:
			- get longitude on sphere with atan2(z, x) which is an angle in radians between [-pi..pi]
			divide by 2*pi -> [-0.5 .. 0.5]; add 0.5 -> [0..1] which is U
			- latitude is acos(some sources say asin?) of y, /pi +0.5 -> [0..1] = V
			https://www.cs.umd.edu/class/spring2013/cmsc425/Lects/lect12.pdf
			https://www.cse.msu.edu/~cse872/tutorial4.html
			- some faces are streched (since some angles are rather flat); complete mess at tesselation >=1 ; TODO

			http://vterrain.org/Textures/spherical.html different approaches
			*/

			float u1 = atan2(p1.z, p1.x) / (2 * glm::pi<float>()) + 0.5f;
			float v1 = acos(p1.y) / glm::pi<float>() + 0.5f;

			float u2 = atan2(p2.z, p2.x) / (2 * glm::pi<float>()) + 0.5f;
			float v2 = acos(p2.y) / glm::pi<float>() + 0.5f;
			if (u2 < 0.75f && u1 > 0.75f){
				u2 += 1.0f;
			}
			else if (u2 > 0.75f && u1 < 0.75f){
				u2 -= 1.0f;
			}

			float u3 = atan2(p3.z, p3.x) / (2 * glm::pi<float>()) + 0.5f;
			float v3 = acos(p3.y) / glm::pi<float>() + 0.5f;
			if (u3 < 0.75f && u2 > 0.75f){
				u3 += 1.0f;
			}
			else if (u3 > 0.75f && u2 < 0.75f){
				u3 -= 1.0f;
			}

			//float v = 1.0f - (acos(n.y) / glm::pi<float>());
			m.texCoords.at(i) = glm::vec2(u1, v1);
			m.texCoords.at(i + 1) = glm::vec2(u2, v2);
			m.texCoords.at(i + 2) = glm::vec2(u3, v3);
		}
	}

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

	//shitty_r@Nd0M_nOiZ3
	for (int i = 0; i < m.indices.size(); i++){
		float r = 1.0f + 0.005f * ((float)rand() / (float)(RAND_MAX));
		m.positions.at(m.indices.at(i)) *= r;
	}
	
	//calculate final normals
	m.normals = std::vector<glm::vec3>(m.indices.size(), glm::vec3(0.0f, 0.0f, 0.0f));
	
	for (unsigned int i = 0; i < m.indices.size(); i += 3)
	{
		int i0 = m.indices.at(i);
		int i1 = m.indices.at(i + 1);
		int i2 = m.indices.at(i + 2);

		glm::vec3 v1 = m.positions.at(i1) - m.positions.at(i0);
		glm::vec3 v2 = m.positions.at(i2) - m.positions.at(i0);

		glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

		m.normals.at(i0) += normal;
		m.normals.at(i1) += normal;
		m.normals.at(i2) += normal;
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

		glm::vec2 ta = m.texCoords.at(m.indices.at(i));
		glm::vec2 tb = m.texCoords.at(m.indices.at(i + 1));
		glm::vec2 tc = m.texCoords.at(m.indices.at(i + 2));

		glm::vec2 tab = (tb + ta) / 2.0f;
		glm::vec2 tac = (tc + ta) / 2.0f;
		glm::vec2 tbc = (tc + tb) / 2.0f;

		glm::vec3 ab = (b + a) / 2.0f;
		glm::vec3 ac = (c + a) / 2.0f;
		glm::vec3 bc = (c + b) / 2.0f;

		//add 3 new vertices to vertex array
		m.positions.push_back(ab);
		m.positions.push_back(bc);
		m.positions.push_back(ac);
		
		//add texCoords
		m.texCoords.push_back(tab);
		m.texCoords.push_back(tac);
		m.texCoords.push_back(tbc);

		// get index of new vertices
		unsigned int iab = find(m.positions.begin(), m.positions.end(), ab) - m.positions.begin();
		unsigned int iac = find(m.positions.begin(), m.positions.end(), ac) - m.positions.begin();
		unsigned int ibc = find(m.positions.begin(), m.positions.end(), bc) - m.positions.begin();

		//index texCoords
		unsigned int itab = find(m.texCoords.begin(), m.texCoords.end(), tab) - m.texCoords.begin();
		unsigned int itac = find(m.texCoords.begin(), m.texCoords.end(), tac) - m.texCoords.begin();
		unsigned int itbc = find(m.texCoords.begin(), m.texCoords.end(), tbc) - m.texCoords.begin();
		
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
