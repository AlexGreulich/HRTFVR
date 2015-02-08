#ifndef HRTFVR_LOADER_CPP
#define HRTFVR_LOADER_CPP

#include "Loader.h"


Loader::Loader(){
	Preload();
}

void Loader::Preload(){
	std::string config = LoadFileContent(PRELOAD_FILE_PATH);

	std::stringstream configStream(config);
	std::string line;
	std::string configContext;

	char removeCharacterList[] = " []";

	while( std::getline(configStream, line, '\n') ){
		for( unsigned int i = 0; i < strlen(removeCharacterList); ++i ){
			line.erase(
				std::remove(line.begin(),
					line.end(),
					removeCharacterList[i]
				),
				line.end()
			);
		}

		if( line.empty() ){
			continue;
		}

		bool isConfigContext = IsConfigContext(&line);

		if( true == isConfigContext ){
			configContext = line;
			continue;
		}

		// if no context is provided: the first 
		// line has to be the context!
		if( configContext.empty() ){
			if( !isConfigContext ){
				LOG(ERROR) << "Could not parse config file: " << PRELOAD_FILE_PATH << " line: " << line;
				return;
			}
		}else{
			if( 0 == configContext.compare("textures") ){
				LoadTexture(line);
			}

			if( 0 == configContext.compare("meshes") ){
				LoadMesh(line);
			}
		}
	}

}

bool Loader::IsConfigContext(std::string* line){
	for( unsigned int i = 0; i < sizeof(m_configurationOptions) / sizeof(m_configurationOptions[0]); i++ ){
		// 0 means equal (Oo)
		if( 0 == m_configurationOptions[i].compare(*line) ){
			return true;
		} 
	}
	return false;
}

void Loader::LoadTexture(std::string pathToFile){
	LOG(DEBUG) << "Loading texture: " << pathToFile;
	m_textureMap[pathToFile] = new Texture(pathToFile);
}

void Loader::LoadCubeTexture(std::string pathToFile){
	LOG(DEBUG) << "Loading CubeMap texture: " << pathToFile;
	m_cubeTextureMap[pathToFile] = new CubeTexture(pathToFile);
}

void Loader::LoadMesh(std::string pathToFile){
	LOG(DEBUG) << "Loading mesh: " << pathToFile;
	m_meshMap[pathToFile] = new Mesh(pathToFile);
}

Mesh* Loader::GetMesh(std::string key){
	if( m_meshMap.find(key) != m_meshMap.end() ){
		return m_meshMap.at(key);
	}

	LOG(ERROR) << "Mesh " << key << " not found";
}

Texture* Loader::GetTexture(std::string key){
	if( m_textureMap.find(key) != m_textureMap.end() ){
		return m_textureMap.at(key);
	}

	LOG(ERROR) << "Texture " << key << " not found";
}

Material* Loader::GetMaterial(std::string key){

}

bool Loader::MeshExists(std::string key){
	return m_meshMap.find(key) != m_meshMap.end();
}

bool Loader::TextureExists(std::string key){
	return m_textureMap.find(key) != m_textureMap.end();

}

bool Loader::MaterialExists(std::string key){

}



std::string Loader::LoadFileContent(std::string pathToFile){
	return LoadFileContent(pathToFile.c_str());
}

std::string Loader::LoadFileContent(const char* pathToFile){

	std::ifstream file;
	file.open(pathToFile);

	std::string content;
	std::string line;

	if (file.is_open()){
		while (file.good()){
			getline(file, line);
			content.append(line + "\n");
		}
	}else{
		LOG(ERROR) << "Unable to load file: " << pathToFile;
	}

	return content;
}

Loader::~Loader(){

}

#endif