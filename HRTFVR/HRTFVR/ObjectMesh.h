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
	GLuint getIboId();

	// vertices
	void setVertices(vector<glm::vec4> vertices);
	GLsizei getVerticesCount();
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
	void setTextureId(GLuint id);
	GLuint getTextureId();
	vector<glm::vec2> getTextures();
	void addTexture(glm::vec2 texture);
	
	// name
	void setName(string filename);
	string getName();

	void allocateBuffers();

	GLuint VERTEX_ARRAY_POSITION = 0;
	GLuint NORMAL_ARRAY_POSITION = 1;
	GLuint TEXTURE_ARRAY_POSITION = 2;


private: 

	string name = "";

	GLuint vboId = 0;
	GLuint vaoId = 0;
	GLuint iboId = 0;

	GLuint indicesId = 0;
	GLuint textureId = 0;

	// parsed vert, norm, tex & faces from .obj
	vector<glm::vec4> vertices;
	vector<glm::vec3> normals;
	vector<glm::vec2> textures;
	vector<glm::vec3> faces;

	// vertex- & index buffer
	vector<GLfloat> vertexBuffer;
	vector<GLfloat> indexBuffer;

	// shortcuts
	GLsizei verticesCount;
	GLuint normalsCount;
	GLuint texturesCount;
	GLuint facesCount;
	
};

