#ifndef HRTFVR_SHADER_CPP
#define HRTFVR_SHADER_CPP

#include "Shader.h"
#include "Logger.h"
#include "Loader.h"
#include <iostream>
#include <fstream>

Shader::Shader(const std::string& fileNameVS, const std::string& fileNameFS)
{
	m_program = glCreateProgram();
	
	m_lightPosition = glm::vec3(0, 100, 100);
	m_lightDirection = glm::vec3(0, 0, 0);

	m_shaders[0] = CreateShader(
		Loader::LoadFileContent(fileNameVS),
		GL_VERTEX_SHADER
	);
	
	m_shaders[1] = CreateShader(
		Loader::LoadFileContent(fileNameFS),
		GL_FRAGMENT_SHADER
	);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
		glAttachShader(m_program, m_shaders[i]);

	glBindAttribLocation(m_program, 0, "position");
	glBindAttribLocation(m_program, 1, "texCoord");
	glBindAttribLocation(m_program, 2, "normal");

	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error linking shader program");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Invalid shader program");

	// MVP
	m_uniforms[UNIFORM_MODEL_MATRIX_LOCATION] = glGetUniformLocation(m_program, "modelMat");
	m_uniforms[UNIFORM_VIEW_MATRIX_LOCATION] = glGetUniformLocation(m_program, "viewMat");
	m_uniforms[UNIFORM_PROJ_MATRIX_LOCATION] = glGetUniformLocation(m_program, "projectionMat");

	// NORMAL
	m_uniforms[UNIFORM_NORMAL_LOCATION] = glGetUniformLocation(m_program, "normalMat");

	// LIGHT
	m_uniforms[UNIFORM_LIGHT_POSITION_LOCATION] = glGetUniformLocation(m_program, "light.position");
	m_uniforms[UNIFORM_LIGHT_DIRECTION_LOCATION] = glGetUniformLocation(m_program, "light.direction");
	m_uniforms[UNIFORM_LIGHT_ATTENTUATION_LOCATION] = glGetUniformLocation(m_program, "light.attentuation");
	m_uniforms[UNIFORM_LIGHT_COLOR_LOCATION] = glGetUniformLocation(m_program, "light.color");
	
	// MATERIAL
	m_uniforms[UNIFORM_MAT_DIFFUSE_LOCATION] = glGetUniformLocation(m_program, "meshMat.diffuse");
	m_uniforms[UNIFORM_MAT_AMBIENT_LOCATION] = glGetUniformLocation(m_program, "meshMat.ambient");
	m_uniforms[UNIFORM_MAT_SPECULAR_LOCATION] = glGetUniformLocation(m_program, "meshMat.specular");
	m_uniforms[UNIFORM_MAT_EMISSIVE_LOCATION] = glGetUniformLocation(m_program, "meshMat.emissive");
	m_uniforms[UNIFORM_MAT_SHINE_LOCATION] = glGetUniformLocation(m_program, "meshMat.shininess");

	// TEXTURE SAMPLER
	m_uniforms[UNIFORM_TEX_SAMPLER_0] = glGetUniformLocation(m_program, "texSampler0");
	m_uniforms[UNIFORM_TEX_SAMPLER_1] = glGetUniformLocation(m_program, "texSampler1");
	m_uniforms[UNIFORM_TEX_SAMPLER_2] = glGetUniformLocation(m_program, "texSampler2");
	m_uniforms[UNIFORM_TEX_SAMPLER_3] = glGetUniformLocation(m_program, "texSampler3");

	// TIME
	m_uniforms[UNIFORM_TIME_LOCATION] = glGetUniformLocation(m_program, "time");

}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(Transform *transform, Camera *camera, Material* mat)
{
	glm::mat4 M = transform->GetModel();
	glm::mat4 V = camera->getView();
	glm::mat4 P = camera->getProjection();

	glm::mat4 Normal = transform->getNormalMat(camera);

	glm::vec4 d = mat->getDiffuse();
	glm::vec4 a = mat->getAmbient();
	glm::vec4 s = mat->getSpecular();
	glm::vec4 e = mat->getEmissive();
	float shiny = mat->getShininess();
	
	UpdateMVP(M, V, P);
	UpdateMaterial(d, a, s, e, shiny);
	UpdateNormalMat(Normal);
	UpdateLightPosition(m_lightPosition);
	UpdateLightDirection(m_lightDirection);
}

void Shader::UpdateMVP(glm::mat4 model, glm::mat4 view, glm::mat4 projection){

	glUniformMatrix4fv(m_uniforms[UNIFORM_MODEL_MATRIX_LOCATION], 1, GL_FALSE, &model[0][0]);
	glUniformMatrix4fv(m_uniforms[UNIFORM_VIEW_MATRIX_LOCATION], 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(m_uniforms[UNIFORM_PROJ_MATRIX_LOCATION], 1, GL_FALSE, &projection[0][0]);	

}

void Shader::UpdateLight(Light* light){
	UpdateLightPosition(light->GetPosition());
	UpdateLightColor(light->GetColor());
}

void Shader::UpdateTime(double* timer){
	glUniform1f(m_uniforms[UNIFORM_TIME_LOCATION], (float) *timer);
}

void Shader::UpdateMaterial(glm::vec4 d,glm::vec4 a,glm::vec4 s,glm::vec4 e,float shiny){
	glUniform4f(m_uniforms[UNIFORM_MAT_DIFFUSE_LOCATION], d.x, d.y, d.z, d.w);
	glUniform4f(m_uniforms[UNIFORM_MAT_AMBIENT_LOCATION], a.x, a.y, a.z, a.w);
	glUniform4f(m_uniforms[UNIFORM_MAT_SPECULAR_LOCATION], s.x, s.y, s.z, s.w);
	glUniform4f(m_uniforms[UNIFORM_MAT_EMISSIVE_LOCATION], e.x, e.y, e.z, e.w);
	glUniform1f(m_uniforms[UNIFORM_MAT_SHINE_LOCATION], shiny);
}

void Shader::UpdateNormalMat(glm::mat4 normal){
	glUniformMatrix4fv(m_uniforms[UNIFORM_NORMAL_LOCATION], 1, GL_FALSE, &normal[0][0]);
}

void Shader::UpdateLightPosition(glm::vec3 lightPosition){
	glUniform3f(m_uniforms[UNIFORM_LIGHT_POSITION_LOCATION], lightPosition.x, lightPosition.y, lightPosition.z);
}

void Shader::UpdateLightColor(glm::vec3 lightColor){
	glUniform3f(m_uniforms[UNIFORM_LIGHT_COLOR_LOCATION], lightColor.r, lightColor.g, lightColor.b);
}

void Shader::UpdateLightDirection(glm::vec3 lightDirection){
	glUniform3f(m_uniforms[UNIFORM_LIGHT_DIRECTION_LOCATION], lightDirection.x, lightDirection.y, lightDirection.z);
}

void Shader::UpdateTextureSampler(GLuint uniform_position, GLuint value){
	glUniform1i(m_uniforms[uniform_position], value);
}

void Shader::SetLightDirection(glm::vec3 direction){
	m_lightDirection = direction;
}

void Shader::SetLightPosition(glm::vec3 position){
	m_lightPosition = position;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 }; 

	if (isProgram)
		glGetProgramiv(shader, flag, &success);
	else
		glGetShaderiv(shader, flag, &success);

	if (success == GL_FALSE)
	{
		if (isProgram)
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);
		else
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		LOG(FATAL) << errorMessage << std::endl << error;
	}
}

GLuint Shader::CreateShader(const std::string& text, unsigned int type)
{
	GLuint shader = glCreateShader(type);

	if (shader == 0)
		std::cerr << "Error compiling shader type " << type << std::endl;

	const char* p[1];
	p[0] = text.c_str();
	GLint lengths[1];
	lengths[0] = text.length();

	glShaderSource(shader, 1, p, lengths);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");

	return shader;
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}

	glDeleteProgram(m_program);
}

#endif