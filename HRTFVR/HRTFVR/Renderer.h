#pragma once

#include <GL/glew.h>  
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <gtc/constants.hpp> // glm constants

using namespace glm;
class Renderer
{
public:
	Renderer();
	~Renderer();

private:
	float fieldOfView;
	float aspectRatio;
	float near_plane;
	float far_plane;

	float y_scale;
	float x_scale;
	float frustum_length = far_plane - near_plane;

	mat4 projectionMatrix, viewMatrix, modelMatrix;
	float viewRatio;// = (float)tan(radians((pi() / (180.0f / fieldOfView) / 2.0f)));

	vec3 avatarPosition, avatarDirection;
};

