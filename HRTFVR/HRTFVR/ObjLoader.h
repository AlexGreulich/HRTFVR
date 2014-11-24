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
	string getBaseDirectory();
	void processFiles();
	~ObjLoader();

private:
	void processFile(const char* filename);
	void parseFile(const char* filename, ObjectMesh *obj);
	map<string, GLuint> meshMap;
	string resourcePath;
	string resourceSearchString;
	string currentDirectory;
	string fileList[];
};

