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

	// vertices
	void setVertices(vector<glm::vec4> vertices);
	vector<glm::vec4> getVertices();
	void addVertex(glm::vec4 vertex);

	// normals
	void setNormals(vector<glm::vec3> normals);
	vector<glm::vec3> getNormals();
	void addNormal(glm::vec3 norm);

	// faces
	void setFaces(vector<glm::vec3> faces);
	vector<glm::vec3> getFaces();
	void addFace(glm::vec3 face);
	
	// textures
	void setTextures(vector<glm::vec2> textures);
	vector<glm::vec2> getTextures();
	void addTexture(glm::vec2 texture);
	
	// name
	void setName(string filename);
	string getName();

	void allocateBuffers();

	void assign();

	const int VERTEX_ARRAY_POSITION = 0;
	const int NORMAL_ARRAY_POSITION = 1;
	const int TEXTURE_ARRAY_POSITION = 2;

	GLuint vboId = 0;
	GLuint vaoId = 0;
	GLuint iboId = 0;
	GLuint indicesId = 0;
	GLuint textureId = 0;
	string name = "";
private: 
	void vbPushVertex(glm::vec3 &face, int i);
	void vbPushNormal(glm::vec3 &face, int i);
	void vbPushTexture(glm::vec3 &face, int i);
	vector<glm::vec4> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> textures;
	vector<GLfloat> indices;
	vector<glm::vec3> faces;
	
};

