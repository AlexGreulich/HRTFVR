#include "ObjectMesh.h"
#include <iostream>

ObjectMesh::ObjectMesh()
{
	glGenVertexArrays(1, &vaoId);
}

GLuint ObjectMesh::getVaoId(){
	return vaoId;
}

GLuint ObjectMesh::getVboId(){
	return vboId;
}

/**
* VERTICES
*/
void ObjectMesh::setVertices(vector<glm::vec4> vertices){
	ObjectMesh::vertices = vertices;
}

vector<glm::vec4> ObjectMesh::getVertices(){
	return ObjectMesh::vertices;
}

void ObjectMesh::addVertex(glm::vec4 vertex){
	ObjectMesh::vertices.push_back(vertex);
}

/**
* NORMALS
*/
void ObjectMesh::setNormals(vector<glm::vec3> normals){
	ObjectMesh::normals = normals;
}

vector<glm::vec3> ObjectMesh::getNormals(){
	return ObjectMesh::normals;
}

void ObjectMesh::addNormal(glm::vec3 norm){
	ObjectMesh::normals.push_back(norm);
}

/**
* FACES
*/
void ObjectMesh::setFaces(vector<glm::vec3> faces){
	ObjectMesh::faces = faces;
}

vector<glm::vec3> ObjectMesh::getFaces(){
	return ObjectMesh::faces;
}

void ObjectMesh::addFace(glm::vec3 face){
	ObjectMesh::faces.push_back(face);
}

/**
 * TEXTURES
 */
void ObjectMesh::setTextures(vector<glm::vec2> textures){
	ObjectMesh::textures = textures;
}

vector<glm::vec2> ObjectMesh::getTextures(){
	return ObjectMesh::textures;
}

void ObjectMesh::addTexture(glm::vec2 texture){
	ObjectMesh::textures.push_back(texture);
}

/**
 * Allocate Buffers on GPU
 */
void ObjectMesh::allocateBuffers(){
	
	int bufferSize = faces.size() * 4 * 3 * 2;
	std::vector<GLfloat> vertexBuffer;

	bool hasFace = false;
	bool hasTexture = false;
	
	// face-vector:
	// one vector represents one slash-delimited value:
	//    i = index, t = texture, n = normal
	//    i
	//    i/t
	//    i/t/n
	for (int i = 0; i < faces.size(); i++){
		glm::vec3 face = faces[i];

		if (face.x >= 0){
			glm::vec4 v1 = vertices.at(face.x);
			vertexBuffer.push_back(v1.x);
			vertexBuffer.push_back(v1.y);
			vertexBuffer.push_back(v1.z);
			vertexBuffer.push_back(v1.w);
		}
		else{
			std::cout << "corrupt vertex index at " << name;
		}

		if ( face.y >= 0 ){
			glm::vec3 n1 = normals.at(face.y);
			vertexBuffer.push_back(n1.x);
			vertexBuffer.push_back(n1.y);
			vertexBuffer.push_back(n1.z);
		}
		else{
			std::cout << "no normals found in " << name;
			glm::vec3 n1;
			vertexBuffer.push_back(n1.x);
			vertexBuffer.push_back(n1.y);
			vertexBuffer.push_back(n1.z);
		}

		
		if (face.z >= 0){
			std::cout << "no textures found in " << name;
			glm::vec2 t1 = textures.at(face.z);
			vertexBuffer.push_back(t1.x);
			vertexBuffer.push_back(t1.y);
		}
		else{
			glm::vec2 t1;
			vertexBuffer.push_back(t1.x);
			vertexBuffer.push_back(t1.y);
		}

	}


	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, 12, &vertexBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(VERTEX_ARRAY_POSITION, 4, GL_FLOAT, GL_FALSE, 36, (void*)0);
	glVertexAttribPointer(NORMAL_ARRAY_POSITION, 3, GL_FLOAT, GL_FALSE, 36, (void*)16);
	glVertexAttribPointer(TEXTURE_ARRAY_POSITION, 2, GL_FLOAT, GL_FALSE, 36, (void*)28);

	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ARRAY_BUFFER, 12, &indices, GL_STATIC_DRAW);

}

/**
* NAME
*/
void ObjectMesh::setName(string name){
	ObjectMesh::name = name;
}
string ObjectMesh::getName(){
	return ObjectMesh::name;
}

void ObjectMesh::assign(){
	//std::cout << "assigned.";
}

ObjectMesh::~ObjectMesh()
{
}
