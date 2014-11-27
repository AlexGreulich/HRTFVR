#pragma once

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/constants.hpp> // glm constants
#include <gtx/reciprocal.hpp>
#include <math.h>
#include <vector>
#include <string>

// static const GLchar *vertexShader = {
// 	"#version 150 core  uniform mat4 projectionMatrix; uniform mat4 viewMatrix; uniform mat4 modelMatrix; in vec4 in_Position; in vec2 in_TextureCoord; out vec2 pass_TextureCoord; void main(void) { 	//gl_Position = in_Position; gl_Position = projectionMatrix * viewMatrix * modelMatrix * in_Position; pass_TextureCoord = in_TextureCoord; }" };

// static const GLchar *fragmentShader = {
// 	"#version 150"
// 	"uniform sampler2D texture_diffuse;"
// 	"in vec2 pass_TextureCoord;"
// 	"out vec4 out_Color;"
// 	"void main(void) {"
// 	"	out_Color = texture(texture_diffuse, pass_TextureCoord);"
// 	"}" };

static const GLchar *vertexShader = "shader.vert";
static const GLchar *fragmentShader = "shader.frag";

class ShaderSetup
{
public:
	ShaderSetup();
	~ShaderSetup();

	GLuint init();
	void destroyShaders();
	GLuint getProjMatrixLoc();
	GLuint getModelMatrixLoc();
	GLuint getViewMatrixLoc();
	GLuint getTexLoc();
	GLuint getAvatarPosLoc();
	GLuint getAvatarViewLoc();
	GLuint getShaderProgram();
	std::string getShaderAsString(const char* filename);
	GLuint shaderProgram;

	static const char getVertexShader();
	static const char getFragmentShader();
private:

	GLuint vShader;
	GLuint fShader;


	GLint projectionMatrixLocation;
	GLint viewMatrixLocation;
	GLint modelMatrixLocation;

	GLint texLocation;

	GLint avatarPositionLocation;
	GLint avatarViewLocation;


};
