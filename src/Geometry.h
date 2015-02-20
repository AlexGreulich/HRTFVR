#pragma once

#include "obj_loader.h"

struct PlatonicSolid
{
public:
	PlatonicSolid(){}
	PlatonicSolid(int i){
		this->setSolidData(i);
	};

	std::vector<glm::vec3> getVertexData(){ return vertexData; }
	std::vector<unsigned int> getConnectivity(){ return connectivity; }

private:	
	int vertexCount;
	int edgeCount;
	int faceCount;
	int p, q;
	std::vector<glm::vec3> vertexData;
	std::vector<unsigned int> connectivity; 

	void setSolidData(int i){
		float sr3 = glm::sqrt(3.0f);
		float a = 1.0f / glm::sqrt(3.0f),
			b = glm::sqrt((3.0f - glm::sqrt(5.0f)) / 6.0f),
			c = glm::sqrt((3.0f + glm::sqrt(5.0f)) / 6.0f);
		float t = (1 + glm::sqrt(5.0f)) / 2.0f;
		float s = glm::sqrt(1.0f + t * t);
		switch (i){
		case(1) :	//TETRAHEDRON
			this->vertexCount = 4;
			this->edgeCount = 6;
			this->faceCount = 4;
			this->p = 3;	// number edges per face
			this->q = 3;	//number edges sharing a vertex

			this->vertexData = {
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(-glm::sqrt(2.0f) / 3.0f, glm::sqrt(6.0f) / 3.0f, float(-1.0f / 3.0f)),
				glm::vec3(2 * glm::sqrt(2.0f) / 3.0f, 0.0f, float(-1.0f / 3.0f)),
				glm::vec3(-glm::sqrt(float(2.0f / 3.0f)), -(glm::sqrt(6.0f) / 3.0f), float(-1.0f / 3.0f))
			};
			this->connectivity = { 1, 2, 3, 0, 2, 3, 0, 3, 1, 1, 3, 2 };
			break;
		case(2) :	//HEXAHEDRON
			this->vertexCount = 8;
			this->edgeCount = 12;
			this->faceCount = 6;
			this->p = 4;
			this->q = 3;
			this->vertexData = {
				glm::vec3(-1.0f / sr3, -1.0f / sr3, -1.0f / sr3),
				glm::vec3(1.0f / sr3, -1.0f / sr3, -1.0f / sr3),
				glm::vec3(1.0f / sr3, 1.0f / sr3, -1.0f / sr3),
				glm::vec3(-1.0f / sr3, 1.0f / sr3, -1.0f / sr3),
				glm::vec3(-1.0f / sr3, -1.0f / sr3, 1.0f / sr3),
				glm::vec3(1.0f / sr3, -1.0f / sr3, 1.0f / sr3),
				glm::vec3(1.0f / sr3, 1.0f / sr3, 1.0f / sr3),
				glm::vec3(-1.0f / sr3, 1.0f / sr3, 1.0f / sr3)
			};
			this->connectivity = {
					0, 3, 2, 0, 2, 1, 0, 1, 5, 0, 5, 4,
					0, 4, 7, 0, 7, 3, 6, 5, 1, 6, 1, 2,
					6, 2, 3, 6, 3, 7, 6, 7, 4, 6, 4, 5,
			};
			break;
		case(3) :	//OCTAHEDRON
			this->vertexCount = 6;
			this->edgeCount = 12;
			this->faceCount = 8;
			this->p = 3;
			this->q = 4;
			this->vertexData = {
				glm::vec3(1.0f, 0.0f, 0.0f),
				glm::vec3(-1.0f, 0.0f, 0.0f),
				glm::vec3(0.0f, 1.0f, 0.0f),
				glm::vec3(0.0f, -1.0f, 0.0f),
				glm::vec3(0.0f, 0.0f, 1.0f),
				glm::vec3(0.0f, 0.0f, -1.0f)
			};
			this->connectivity = {
					4, 0, 2, 4, 2, 1, 4, 1, 3, 4, 3, 0,
					5, 2, 0, 5, 1, 2, 5, 3, 1, 5, 0, 3
			};
			break;
		case(4) :	//DODECAHEDRON
			this->vertexCount = 20;
			this->edgeCount = 30;
			this->faceCount = 12;
			this->p = 5;
			this->q = 3;
			this->vertexData = {
				glm::vec3(a, a, a), glm::vec3(a, a, -a), glm::vec3(a, -a, a), glm::vec3(a, -a, -a), glm::vec3(-a, a, a),
				glm::vec3(-a, a, -a), glm::vec3(-a, -a, a), glm::vec3(-a, -a, -a), glm::vec3(b, c, 0.0f), glm::vec3(-b, c, 0.0f),
				glm::vec3(b, -c, 0.0f), glm::vec3(-b, -c, 0.0f), glm::vec3(c, 0.0f, b), glm::vec3(c, 0.0f, -b), glm::vec3(-c, 0.0f, b),
				glm::vec3(-c, 0.0f, -b), glm::vec3(0.0f, b, c), glm::vec3(0.0f, -b, c), glm::vec3(0.0f, b, -c), glm::vec3(0.0f, -b, -c),
			};
			this->connectivity = {
					0, 8, 9, 0, 9, 4, 0, 4, 16, 0, 12, 13, 0, 13, 1, 0, 1, 8,
					0, 16, 17, 0, 17, 2, 0, 2, 12, 8, 1, 18, 8, 18, 5, 8, 5, 9,
					12, 2, 10, 12, 10, 3, 12, 3, 13, 16, 4, 14, 16, 14, 6, 16, 6, 17,
					9, 5, 15, 9, 15, 14, 9, 14, 4, 6, 11, 10, 6, 10, 2, 6, 2, 17,
					3, 19, 18, 3, 18, 1, 3, 1, 13, 7, 15, 5, 7, 5, 18, 7, 18, 19,
					7, 11, 6, 7, 6, 14, 7, 14, 15, 7, 19, 3, 7, 3, 10, 7, 10, 11
			};
			break;
		case(5) :	//ICOSAHEDRON
			this->vertexCount = 12;
			this->edgeCount = 30;
			this->faceCount = 20;
			this->p = 3;
			this->q = 5;
			this->vertexData = {				
				glm::vec3(t, 1.0f, 0.0f), 
				glm::vec3(-t, 1.0f, 0.0f), 
				glm::vec3(t, -1.0f, 0.0f),
				glm::vec3(-t, -1.0f, 0.0f), 

				glm::vec3(1.0f, 0.0f, t), 
				glm::vec3(1.0f, 0.0f, -t),
				glm::vec3(-1.0f, 0.0f, t), 
				glm::vec3(-1.0f, 0.0f, -t), 

				glm::vec3(0.0f, t, 1.0f),
				glm::vec3(0.0f, -t, 1.0f), 
				glm::vec3(0.0f, t, -1.0f), 
				glm::vec3(0.0f, -t, -1.0f)
			};
			this->connectivity = {
				0, 8, 4, 1, 10, 7, 2, 9, 11, 7, 3, 1, 
				0, 5, 10, 3, 9, 6, 3, 11, 9, 8, 6, 4, 
				2, 4, 9, 3, 7, 11, 4, 2, 0, 9, 4, 6, 
				2, 11, 5, 0, 10, 8, 5, 0, 2, 10, 5, 7, 
				1, 6, 8,1, 8, 10,6, 1, 3,11, 7, 5	
			};
			break;
		}
	}
};

class Geometry
{
private:
	
public:
	Geometry(int platonicType);
	~Geometry();
	PlatonicSolid ps;
	IndexedModel toIndexedModel(int tess, float scale);
	IndexedModel tesselateMesh(IndexedModel m);
	void scaleMesh(int s);
};

