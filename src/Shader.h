#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "Transform.h"
#include "Mesh.h"
#include "Logger.h"
#include "Light.h"

class Shader
{
public:
	Shader(const std::string& fileNameVS, const std::string& fileNameFS);

	void Bind();

	// Update Methods
	void Update(Transform *transform, Camera *camera, Material* mat);
	void UpdateMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
	void UpdateMaterial(glm::vec4 d, glm::vec4 a,glm::vec4 s,glm::vec4 e,float shiny);
	void UpdateNormalMat(glm::mat4 normal);
	void UpdateTime(double* timer);
	void UpdateLightPosition(glm::vec3 lightPosition);
	void UpdateLightColor(glm::vec3 lightColor);
	void UpdateLightDirection(glm::vec3 lightDirection);
	void UpdateTextureSampler(GLuint sampler, GLuint value);
	void UpdateLight(Light* light);
	void ToggleFog();

	// Setter Methods
	void SetLightDirection(glm::vec3 direction);
	void SetLightPosition(glm::vec3 position);

	// TEXTURE SAMPLER
	static const unsigned int UNIFORM_TEX_SAMPLER_0 = 100;
	static const unsigned int UNIFORM_TEX_SAMPLER_1 = 101;
	static const unsigned int UNIFORM_TEX_SAMPLER_2 = 102;
	static const unsigned int UNIFORM_TEX_SAMPLER_3 = 103;

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;

	// this causes a heap lo/hi size mismatch
	// if the NUM is too low 
	static const unsigned int NUM_UNIFORMS = 1024;

	// MVP
	static const unsigned int UNIFORM_MODEL_MATRIX_LOCATION = 0;
	static const unsigned int UNIFORM_VIEW_MATRIX_LOCATION = 1;
	static const unsigned int UNIFORM_PROJ_MATRIX_LOCATION = 2;

	static const unsigned int UNIFORM_NORMAL_LOCATION = 10;

	// LIGHT
	static const unsigned int UNIFORM_LIGHT_DIRECTION_LOCATION = 20;
	static const unsigned int UNIFORM_LIGHT_POSITION_LOCATION = 21;
	static const unsigned int UNIFORM_LIGHT_COLOR_LOCATION = 22;
	static const unsigned int UNIFORM_LIGHT_ATTENTUATION_LOCATION = 23;

	// FOG
	static const unsigned int UNIFORM_FOG_ENABLED = 30;

	// TIME
	static const unsigned int UNIFORM_TIME_LOCATION = 40;


	// MATERIAL
	static const unsigned int UNIFORM_MAT_DIFFUSE_LOCATION = 50;
	static const unsigned int UNIFORM_MAT_AMBIENT_LOCATION = 51;
	static const unsigned int UNIFORM_MAT_SPECULAR_LOCATION = 52;
	static const unsigned int UNIFORM_MAT_EMISSIVE_LOCATION = 53;
	static const unsigned int UNIFORM_MAT_SHINE_LOCATION = 54;

	Shader(const Shader& shader) {}

	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	glm::vec3 m_lightPosition;
	glm::vec3 m_lightDirection;

	bool m_fogEnabled;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif