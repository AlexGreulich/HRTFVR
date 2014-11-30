#ifndef SHADER_INCLUDED_H
#define SHADER_INCLUDED_H

#include <string>
#include <GL/glew.h>
#include "transform.h"

class Shader
{
public:
	Shader(const std::string& fileName);

	void Bind();
	void Update(Transform *transform, Camera *camera);

	virtual ~Shader();
protected:
private:
	static const unsigned int NUM_SHADERS = 2;
	static const unsigned int NUM_UNIFORMS = 3;
	static const unsigned int UNIFORM_MVP_LOCATION = 0;
	static const unsigned int UNIFORM_NORMAL_LOCATION = 1;
	static const unsigned int UNIFORM_LIGHT_DIRECTION_LOCATION = 2;

	Shader(const Shader& shader) {}

	std::string LoadShader(const std::string& fileName);
	void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	GLuint CreateShader(const std::string& text, unsigned int type);

	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORMS];
};

#endif