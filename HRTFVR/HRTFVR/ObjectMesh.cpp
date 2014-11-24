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
void ObjectMesh::setFaces(vector<GLushort> faces){
	ObjectMesh::faces = faces;
}

vector<GLushort> ObjectMesh::getFaces(){
	return ObjectMesh::faces;
}

void ObjectMesh::addFace(GLushort face){
	ObjectMesh::faces.push_back(face);
}

/**
 * TEXTURES
 * -- ignoring textures for now --
 *
void ObjectMesh::setTextures(vector<glm::vec2> textures){
	ObjectMesh::textures = textures;
}

vector<glm::vec2> ObjectMesh::getTextures(){
	return ObjectMesh::textures;
}

void ObjectMesh::addTexture(glm::vec2 texture){
	ObjectMesh::textures.push_back(texture);
}
*/

/**
 * Allocate Buffers on GPU
 */
void ObjectMesh::allocateBuffers(){

	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, 12, &vertices, GL_STATIC_DRAW);

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
