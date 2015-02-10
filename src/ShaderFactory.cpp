#ifndef HRTFVR_SHADER_FACTORY_CPP
#define HRTFVR_SHADER_FACTORY_CPP

#include "ShaderFactory.h"
#include "Logger.h"

void ShaderFactory::CreateShader(
	std::string name,
	std::string vertexShader,
	std::string fragmentShader
){
	LOG(DEBUG) << "creating shader: " << name;
	m_shaders[name] = new Shader(vertexShader, fragmentShader);
}

Shader* ShaderFactory::GetShader(std::string name){
	
	std::map<std::string, Shader*>::iterator it;

	it = m_shaders.find(name);

	if( it != m_shaders.end() ){
		return it->second;
	}else{
		LOG(FATAL) << "Shader not found: " << name;
	}
}

ShaderFactory::~ShaderFactory(){
	for( std::map<std::string, Shader*>::iterator it = m_shaders.begin(); it != m_shaders.end(); ++it ){
		delete (*it).second;
	}
}

#endif