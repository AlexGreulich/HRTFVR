#ifndef HRTFVR_SHADER_FACTORY_H
#define HRTFVR_SHADER_FACTORY_H

#include <string>
#include <GL/glew.h>
#include <map>
#include <string>
#include "Shader.h"

class ShaderFactory{

public:
	static ShaderFactory& GetInstance(){
		static ShaderFactory instance;
		return instance;
	}

	void CreateShader(std::string name, std::string vertexShader, std::string fragmentShader);
	Shader* GetShader(std::string name);

	~ShaderFactory();

private:
	ShaderFactory() {};

	std::map<std::string, Shader*> m_shaders;

	// http://stackoverflow.com/questions/1008019/c-singleton-design-pattern
	ShaderFactory(ShaderFactory const&) = delete;
	void operator=(ShaderFactory const &) = delete;

};

#endif