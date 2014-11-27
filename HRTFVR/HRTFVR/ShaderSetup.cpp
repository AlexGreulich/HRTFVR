#include "ShaderSetup.h"
#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

ShaderSetup::ShaderSetup()
	: vShader(0),
	fShader(0),
	shaderProgram(0),
	projectionMatrixLocation(0),
	viewMatrixLocation(0),
	modelMatrixLocation(0),
	texLocation(0),
	avatarPositionLocation(0),
	avatarViewLocation(0)
{
	init();
}

GLuint ShaderSetup::init(){
	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cout << "OpenGL Error: " << error << std::endl;
	}

	const char* vshader = getShaderAsString(vertexShader);

	//Vertex shader
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, (const GLchar**)&vshader, NULL);
	glCompileShader(vShader);

	GLint vsCompiled;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vsCompiled);
	if (vsCompiled){
		std::cout << "Vertex shader compiled";
	}
	/*
	String vertexShaderErrorLog = glGetShaderInfoLog(vertexShader, 65536);
	if (vertexShaderErrorLog.length() != 0) {System.err.println("Vertex shader compile log: \n" + vertexShaderErrorLog);}
	*/

	const char* fshader = getShaderAsString(vertexShader);

	//Fragment shader
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, (const GLchar**)&fshader, NULL);
	glCompileShader(fShader);

	/*
	String fragmentShaderErrorLog = glGetShaderInfoLog(fragmentShader, 65536);
	if (fragmentShaderErrorLog.length() != 0) {System.err.println("Fragment shader compile log: \n" + fragmentShaderErrorLog);}
	*/

	//Shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	glBindAttribLocation(shaderProgram, 0, "in_Position");

	// Texture -> attribute 1
	glBindAttribLocation(shaderProgram, 1, "in_TextureCoord");

	glLinkProgram(shaderProgram);
	glValidateProgram(shaderProgram);

	glDetachShader(shaderProgram, vShader);
	glDetachShader(shaderProgram, fShader);
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	// Get uniform locations
	projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");

	avatarPositionLocation = glGetUniformLocation(shaderProgram, "avatarPos");
	avatarViewLocation = glGetUniformLocation(shaderProgram, "avatarDir");

	texLocation = glGetUniformLocation(shaderProgram, "tex0");


	glUseProgram(shaderProgram);
	glUniform1i(texLocation, 0);

	glUseProgram(0);

	/*
	String log = glGetProgramInfoLog(shaderProgram, 65536);
	if (log.length() != 0) {
	System.err.println("Program link log:\n" + log);
	}
	*/
	return shaderProgram;
}

void ShaderSetup::destroyShaders(){
	glDetachShader(shaderProgram, vShader);
	glDetachShader(shaderProgram, fShader);

	glDeleteShader(vShader);
	glDeleteShader(fShader);
	glDeleteProgram(shaderProgram);
}

// Getter
GLuint ShaderSetup::getProjMatrixLoc(){
	return projectionMatrixLocation;
}
GLuint ShaderSetup::getModelMatrixLoc(){
	return modelMatrixLocation;
}
GLuint ShaderSetup::getViewMatrixLoc(){
	return viewMatrixLocation;
}
GLuint ShaderSetup::getTexLoc(){
	return texLocation;
}
GLuint ShaderSetup::getAvatarPosLoc(){
	return avatarPositionLocation;
}
GLuint ShaderSetup::getAvatarViewLoc(){
	return avatarViewLocation;
}

GLuint ShaderSetup::getShaderProgram(){
	return shaderProgram;
}

const char* ShaderSetup::getShaderAsString(const char* filename){
	
	// build path to filename
	string base = ObjLoader::getBaseDirectory();
	string shaderPath = base + "Resources\\Shaders\\";
	shaderPath.append(filename);

	ifstream in(shaderPath, ios::in);

	if( !in ){
		std::cout << "Cannot open " << shaderPath << std::endl;
	}

	string line;
	string total;

	while ( getline(in, line) ){
		total.append(line);
	}

	return total.c_str();

}