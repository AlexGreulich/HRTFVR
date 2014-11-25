#define _CRT_SECURE_NO_DEPRECATE

#include "ObjLoader.h"
#include <Windows.h>
#include <stdio.h>
#include <glm.hpp>
#include <vector>
#include <glm.hpp>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdint.h>
#include <stdlib.h>
/*
 * ObjLoader loads .obj files
 */
using namespace std;

ObjLoader::ObjLoader()
{
	meshMap;
	textureMap;
}	

void ObjLoader::processFiles(){
	HANDLE hFind;
	WIN32_FIND_DATA data;
	cout << "process files";
	currentDirectory = getBaseDirectory();
	resourcePath = currentDirectory + "Resources\\";
	resourceSearchString = resourcePath + "*";

	cout << "resource path: " << resourceSearchString << endl;

	hFind = FindFirstFile(resourceSearchString.c_str(), &data);

	if (hFind != INVALID_HANDLE_VALUE){
		do {
			printf("processing file: %s\n", data.cFileName);
			processFile(data.cFileName);
		} while (FindNextFile(hFind, &data));
		FindClose(hFind);
	}
	else{
		cout << "Error processing files: " << GetLastError();
	}
}

void ObjLoader::processFile( const char* filename ){
	string fn = string(filename);
	string ending = fn.substr(fn.find_last_of(".") + 1);

	//int length = fn.length;
	
	string beginning = fn.substr(0, fn.find_last_of(".")+1);

	if (ending == "obj"){
		ObjectMesh *obj = new ObjectMesh();
		obj->setName( string(filename) );
	
		parseFile(filename, obj);

		obj->allocateBuffers();
		meshMap[ obj->getName() ] = obj->getVboId();
		//string z = obj->getName();
		textureMap[ obj->getName() ]= parseTexture(beginning.append(".png"));
	}
	
	
	else if(ending =="png" ){
		//parseTexture();
		
	}




	//std::cout << "VBO: " << obj->getName() << " : " << obj->getVboId() << endl;


}

void ObjLoader::parseFile( const char* filename, ObjectMesh *obj ){
	
	string filePath(resourcePath);
	filePath.append(filename);

	//cout << "processing file: " << filePath << endl;
	ifstream in(filePath, ios::in);

	if (!in){
		cout << "Cannot open " << filePath << endl;
	}
	string line;
	while (getline(in, line)) {
		// http://en.wikibooks.org/wiki/OpenGL_Programming/Modern_OpenGL_Tutorial_Load_OBJ
		if (line.substr(0, 2) == "v "){
			istringstream s(line.substr(2));
			glm::vec4 v;
			s >> v.x;
			s >> v.y;
			s >> v.z;
			v.w = 1.0f;
			obj->addVertex(v);
		}
		/*else if (line.substr(0, 2) == "vn"){
			istringstream s(line.substr(2));
			glm::vec3 norm;
			s >> norm.x;
			s >> norm.y;
			s >> norm.z;
			obj->addNormal(norm);

		}
		else if (line.substr(0, 2) == "f "){
			istringstream s(line.substr(2));
			GLushort a, b, c;
			s >> a;
			s >> b;
			s >> c;
			a--;
			b--;
			c--;
			obj->addFace(a);
			obj->addFace(b);
			obj->addFace(c);
		}
		else if (line.substr(2) == "vt"){
			istringstream s(line.substr(2));
			glm::vec2 texture;
			s >> texture.x;
			s >> texture.y;
			obj->addTexture(texture);
		}*/
	}
}

GLuint ObjLoader::parseTexture(string filename){
	GLuint texture;

	int width, height;

	unsigned char * data;

	FILE * file;

	fopen_s(&file, filename.c_str(), "rb");

	if (file == NULL){ return 0; };
	width = 1024;
	height = 512;
	data = (unsigned char *)malloc(width * height * 3);
	//int size = fseek(file,);
	fread(data, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i < width * height; ++i)
	{
		int index = i * 3;
		unsigned char B, R;
		B = data[index];
		R = data[index + 2];

		data[index] = R;
		data[index + 2] = B;

	}


	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);


	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
	free(data);

	return texture;
}

string ObjLoader::getBaseDirectory(){
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	
	return string(buffer).substr(0, pos) + "\\..\\";
}

GLuint ObjLoader::getMeshByName(string filename ){
	unordered_map<string, GLuint>::iterator i = meshMap.find(filename);
	return i->second;//textureMap[filename];
	//return meshMap[filename];
}

GLuint ObjLoader::getTexByName(string filename){
	unordered_map<string, GLuint>::iterator i = textureMap.find(filename);
	return i->second;//textureMap[filename];
}
ObjLoader::~ObjLoader()
{

}
