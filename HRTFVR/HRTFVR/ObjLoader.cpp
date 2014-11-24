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

/*
 * ObjLoader loads .obj files
 */
using namespace std;

ObjLoader::ObjLoader()
{
}	

void ObjLoader::processFiles(){
	HANDLE hFind;
	WIN32_FIND_DATA data;
	cout << "process files";
	currentDirectory = getBaseDirectory();
	resourcePath = currentDirectory + "Resources\\";
	resourceSearchString = resourcePath + "*.obj";

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

	ObjectMesh *obj = new ObjectMesh();
	obj->setName( string(filename) );

	parseFile(filename, obj);

	obj->allocateBuffers();
	meshMap[ obj->getName() ] = obj->getVboId();

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

string ObjLoader::getBaseDirectory(){
	char buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	string::size_type pos = string(buffer).find_last_of("\\/");
	
	return string(buffer).substr(0, pos) + "\\..\\";
}


ObjLoader::~ObjLoader()
{

}
