#include "ObjectMesh.h"
#include <iostream>

using namespace std;

ObjectMesh::ObjectMesh()
{}

GLuint ObjectMesh::getVaoId(){
	return vaoId;
}

GLuint ObjectMesh::getVboId(){
	return vboId;
}

GLuint ObjectMesh::getIboId(){
	return iboId;
}

/**
* VERTICES
*/
void ObjectMesh::setVertices(vector<glm::vec4> vertices){
	ObjectMesh::vertices = vertices;
}

GLsizei ObjectMesh::getVerticesCount(){
	return ObjectMesh::verticesCount;
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

void ObjectMesh::setTextureId(GLuint id){
	ObjectMesh::textureId = id;
}

GLuint ObjectMesh::getTextureId(){
	return ObjectMesh::textureId;
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
	
	cout << "allocating buffers for " << name << endl;
	
	verticesCount = vertices.size();
	normalsCount = normals.size();
	texturesCount = textures.size();
	facesCount = faces.size();

	// iterate over face-vector:
	// one vector (one iteration) represents one slash-delimited value from the .obj file:
	//    i = index, t = texture, n = normal
	//    i
	//    i/t
	//    i/t/n
	//  the buffer multiplexes the data like that:
	//  vertex(4) - normal(3) - texture(2)
	//  vertexbuffer = [v.x, v.y, v.z, v.w, t.x, t.y, n.x, n.y, n.z, ... ]
	//
	//  face stores vectors like that: 
	//  x -> pointer to vertex
	//  y -> pointer to normal
	//  z -> pointer to texture
	// 
	for (int i = 0; i < faces.size(); i++){
		glm::vec3 face = faces[i];

		// append vertex
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

		// append normal
		if (face.z >= 0){
			glm::vec3 n1 = normals.at(face.z);
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

		// append texture
		if (face.y >= 0){

			glm::vec2 t1 = textures.at(face.y);
			vertexBuffer.push_back(t1.x);
			vertexBuffer.push_back(t1.y);
		}
		else{
			std::cout << "no textures found in " << name;
			glm::vec2 t1;
			vertexBuffer.push_back(t1.x);
			vertexBuffer.push_back(t1.y);
		}

		
		
		indexBuffer.push_back(i);
	}

	// generate & bind this VAO
	glGenVertexArrays(1, &vaoId);
	glBindVertexArray(vaoId);

	// gen VBO & write into vbo
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, (verticesCount + normalsCount + texturesCount)*sizeof(GLfloat), &vertexBuffer, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(VERTEX_ARRAY_POSITION, 4, GL_FLOAT, GL_FALSE, 36, (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(NORMAL_ARRAY_POSITION, 3, GL_FLOAT, GL_FALSE, 36, (void*)16);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(TEXTURE_ARRAY_POSITION, 2, GL_FLOAT, GL_FALSE, 36, (void*)28);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// reset VAO
	glBindVertexArray(0);
	// create ibo
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 36 , &indexBuffer, GL_STATIC_DRAW);	//hard coded! 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);



	cout << "vaoID: " << vaoId << endl;
	cout << "vboID: " << vboId << endl;
	cout << "iboID: " << iboId << endl;
	
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

ObjectMesh::~ObjectMesh()
{
}
