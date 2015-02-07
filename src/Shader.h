#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Mesh.h"
#include "Logger.h"

class Shader
{
public:
	Shader(const std::string& fileNameVS, const std::string& fileNameFS);

	void Bind();
	void Update(Transform *transform, Camera *camera, Material* mat);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;

	// this causes a heap lo/hi size mismatch
	// if the NUM is too low 
	static const unsigned int NUM_UNIFORMS = 16;

	static const unsigned int UNIFORM_MODEL_MATRIX_LOCATION = 0;
	static const unsigned int UNIFORM_VIEW_MATRIX_LOCATION = 1;
	static const unsigned int UNIFORM_PROJ_MATRIX_LOCATION = 2;

	static const unsigned int UNIFORM_NORMAL_LOCATION = 3;
	static const unsigned int UNIFORM_LIGHT_DIRECTION_LOCATION = 4;
	static const unsigned int UNIFORM_LIGHT_POSITION_LOCATION = 5;

	static const unsigned int UNIFORM_LIGHT_SOURCE_DIFFUSE_LOCATION = 6;
	static const unsigned int UNIFORM_LIGHT_SOURCE_AMBIENT_LOCATION = 7;
	static const unsigned int UNIFORM_LIGHT_SOURCE_SPECULAR_LOCATION = 8;
	
	static const unsigned int UNIFORM_MAT_DIFFUSE_LOCATION = 9;
	static const unsigned int UNIFORM_MAT_AMBIENT_LOCATION = 10;
	static const unsigned int UNIFORM_MAT_SPECULAR_LOCATION = 11;
	static const unsigned int UNIFORM_MAT_EMISSIVE_LOCATION = 12;
	static const unsigned int UNIFORM_MAT_SHINE_LOCATION = 13;


	Shader(const Shader& shader) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif