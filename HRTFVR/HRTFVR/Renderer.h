#pragma once

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/constants.hpp> // glm constants
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtx/reciprocal.hpp>
#include <math.h>
#include <vector>
#include "ShaderSetup.h"
#include "ObjLoader.h"

using namespace glm;

class Renderer
{
public:
	Renderer(GLuint w, GLuint h);
	~Renderer();
	//void uploadMatrix(vector<float> &matrix);

	void destroyGL();

	void render(string meshHandle);
	ObjLoader* loader;
private:

	ShaderSetup* shaders;
	float fieldOfView;
	float aspectRatio;
	float near_plane;
	float far_plane;

	float y_scale;
	float x_scale;
	float frustum_length;
		
	float viewRatio;

	vec3 avatarPosition;
	vec3 avatarDirection;
	mat4 projectionMatrix;
	mat4 viewMatrix;
	mat4 modelMatrix;

	void initOpenGL(int w, int h);
	void setupMatrices();
	void calcAndUploadViewMatrix();
	void calcAndUploadModelMatrix();
};

