#include "Renderer.h"
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
//#include <gtc/constants.hpp> // glm constants
//#include <gtx/reciprocal.hpp>
#include <math.h>
#include <vector>
#include <iostream>

using namespace std;
using namespace glm;


Renderer::Renderer(GLuint w, GLuint h)
	: projectionMatrix(mat4(0.0)),
	viewMatrix(mat4(0.0)),
	modelMatrix(mat4(0.0)),
	fieldOfView(60.0f),
	aspectRatio(w / h),
	near_plane(0.1f),
	far_plane(1000.0f),
	y_scale(tan(M_PI_2 - (radians(fieldOfView / 2)))),
	x_scale(y_scale / aspectRatio),
	frustum_length(far_plane - near_plane),
	viewRatio(tan(radians((M_PI / (180.0 / fieldOfView) / 2.0))))
{
	shaders = new ShaderSetup();
	initOpenGL(w, h);
	setupMatrices();
	loader = new ObjLoader();
	loader->processFiles();
}


Renderer::~Renderer()
{
	destroyGL();
}


void Renderer::initOpenGL(int w, int h){

	glShadeModel(GL_SMOOTH);

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, w, h);
	glDepthFunc(GL_LEQUAL);
	//glEnable(GL_CULL_FACE);
	//glFrontFace(GL_CCW);
	//glCullFace(GL_FRONT);
}

void Renderer::setupMatrices(){
	projectionMatrix = perspective(fieldOfView, aspectRatio, near_plane, far_plane);
	cout << "shaderprogramID: " << shaders->getShaderProgram() << endl;
	glUseProgram(shaders->shaderProgram);
	glUniformMatrix4fv(shaders->getProjMatrixLoc(), 1, GL_FALSE, value_ptr(projectionMatrix));
	glUseProgram(0);
	calcAndUploadModelMatrix();
	calcAndUploadViewMatrix();

}

void Renderer::calcAndUploadModelMatrix(){
	modelMatrix = mat4(0.0);
	glUseProgram(shaders->getShaderProgram());
	glUniformMatrix4fv(shaders->getModelMatrixLoc(), 1, GL_FALSE, value_ptr(modelMatrix));
	glUseProgram(0);
}

void Renderer::calcAndUploadViewMatrix(){
	viewMatrix = lookAt(
		vec3(0.0, 2.0, 2.0), //eye
		vec3(0.0, 0.0, 0.0), //center
		vec3(0.0, 1.0, 0.0));	//up
	glUseProgram(shaders->getShaderProgram());
	glUniformMatrix4fv(shaders->getViewMatrixLoc(), 1, GL_FALSE, value_ptr(viewMatrix));
	glUseProgram(0);
}

void Renderer::destroyGL(){

}

void Renderer::render(string meshHandle){
	//GLuint meshID = ;
	//GLuint texID = ;
	ObjectMesh *mesh = loader->getMeshByName(meshHandle);
	
	if (mesh == NULL){
		cout << "could not find mesh with handle " << meshHandle;
		throw;
	}

	glUseProgram(shaders->getShaderProgram());
	glBindTexture(GL_TEXTURE_2D, mesh->getTextureId());
	glBindVertexArray(mesh->getVaoId());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		//get IBO
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->getIboId() );
			glDrawElements(GL_TRIANGLES, mesh->getVerticesCount(), GL_UNSIGNED_SHORT, (void*)0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
	
	glBindVertexArray(0);

	glBindTexture(GL_TEXTURE_2D, 0);
	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glFlush();

}
