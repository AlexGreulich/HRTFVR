#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <glm.hpp>
#include <GL\glew.h>
#include <map>
#include "ObjectMesh.h"

using namespace std;

class ObjLoader
{
public:
	ObjLoader();
	static string getBaseDirectory();
	void processFiles();
	~ObjLoader();
	map<string, ObjectMesh*> meshMap;
	ObjectMesh* getMeshByName(string name);

	map<string, GLuint> textureMap;
	GLuint getTexByName(string name);

private:
	void processFile(const char* filename);
	void parseFile(const char* filename, ObjectMesh *obj);
	GLuint parseTexture(string filename);

	string resourcePath;
	string resourceSearchString;
	string currentDirectory;
	//string fileList[];
};

