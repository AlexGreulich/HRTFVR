#pragma once

#include <string>
#include <vector>
#include <string>
#include <glm.hpp>
#include <Windows.h>
#include <GL\glew.h>
#include <GL\GL.h>

using namespace std;

class ObjectMesh
{
public:
	ObjectMesh();
	~ObjectMesh();

	GLuint getVaoId();
	GLuint getVboId();

	void setVertices(vector<glm::vec4> vertices);
	vector<glm::vec4> getVertices();
	void addVertex(glm::vec4 vertex);

	void setNormals(vector<glm::vec3> normals);
	vector<glm::vec3> getNormals();
	void addNormal(glm::vec3 norm);

	void setFaces(vector<GLushort> faces);
	vector<GLushort> getFaces();
	void addFace(GLushort face);
	/*
	void setTextures(vector<glm::vec2> textures);
	vector<glm::vec2> getTextures();
	void addTexture(glm::vec2 texture);
	*/
	void setName(string filename);
	string getName();

	void allocateBuffers();

	void assign();

	const int ATTRIBUTE_VERTEX = 0;
	const int ATTRIBUTE_NORMALS = 1;
	const int ATTRIBUTE_FACES = 2;
	GLuint vboId = 0;
	GLuint vaoId = 0;
	GLuint iboId = 0;
	GLuint indicesId = 0;
	GLuint textureId = 0;
	string name = "";
private: 
	

	vector<glm::vec4> vertices;
	vector<GLuint> indices;
	vector<glm::vec3> normals;
	vector<glm::vec2> textures;
	vector<GLushort> faces;
	
};

