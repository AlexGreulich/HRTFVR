#include "ShaderSetup.h"
#include "ObjLoader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
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

	std::string vshader = getShaderAsString(vertexShader);
	const GLchar *vsource = (const GLchar *)vshader.c_str();
	
	//Vertex shader
	vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vsource, NULL);
	glCompileShader(vShader);

	std::cout << vshader;

	GLint vsCompiled;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vsCompiled);
	if (vsCompiled){
		std::cout << "Vertex shader compiled" << std::endl;
	}

	/*
	String vertexShaderErrorLog = glGetShaderInfoLog(vertexShader, 65536);
	if (vertexShaderErrorLog.length() != 0) {System.err.println("Vertex shader compile log: \n" + vertexShaderErrorLog);}
	*/

	std::string fshader = getShaderAsString(fragmentShader);
	const GLchar *fsource = (const GLchar *)fshader.c_str();
	//Fragment shader
	fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fsource, NULL);
	glCompileShader(fShader);

	GLint fsCompiled;
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fsCompiled);
	if (fsCompiled){
		std::cout << "Fragment shader compiled" << std::endl;
	}

	/*
	String fragmentShaderErrorLog = glGetShaderInfoLog(fragmentShader, 65536);
	if (fragmentShaderErrorLog.length() != 0) {System.err.println("Fragment shader compile log: \n" + fragmentShaderErrorLog);}
	*/

	//Shader program
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);

	glBindAttribLocation(shaderProgram, 0, "in_Position");

	glBindAttribLocation(shaderProgram, 1, "in_Normal");

	glBindAttribLocation(shaderProgram, 2, "in_TextureCoord");

	glLinkProgram(shaderProgram);
	GLint linkResult;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &linkResult);
	
	
	if (linkResult == GL_FALSE){
		GLint length;
		
		/* get the program info log */
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &length);
		char *infoLog = (char *)malloc(length);

		glGetProgramInfoLog(shaderProgram, length, &linkResult, infoLog);

		/* print an error message and the info log */
		fprintf(stderr, "ShaderSetup::init(): Program linking failed: %s\n", infoLog);

		/* delete the program */
		glDeleteProgram(shaderProgram);
		shaderProgram = 0;
		throw;
	}

	glValidateProgram(shaderProgram);

	glDetachShader(shaderProgram, vShader);
	glDetachShader(shaderProgram, fShader);
	glDeleteShader(vShader);
	glDeleteShader(fShader);

	// Get uniform locations
	projectionMatrixLocation = glGetUniformLocation(shaderProgram, "projectionMatrix");
	viewMatrixLocation = glGetUniformLocation(shaderProgram, "viewMatrix");
	modelMatrixLocation = glGetUniformLocation(shaderProgram, "modelMatrix");

	//avatarPositionLocation = glGetUniformLocation(shaderProgram, "avatarPos");
	//avatarViewLocation = glGetUniformLocation(shaderProgram, "avatarDir");

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

std::string ShaderSetup::getShaderAsString(const char* filename){
	
	// build path to filename
	string base = ObjLoader::getBaseDirectory();
	string shaderPath = base + "Resources\\Shaders\\";
	shaderPath.append(filename);

	ifstream in(shaderPath, ios::in);

	if( !in ){
		std::cout << "Cannot open " << shaderPath << std::endl;
	}

	std::string content((std::istreambuf_iterator<char>(in)),
		(std::istreambuf_iterator<char>()));

	return content;

}