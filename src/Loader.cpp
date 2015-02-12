#ifndef HRTFVR_LOADER_CPP
#define HRTFVR_LOADER_CPP

#include "Loader.h"
#include <sstream>

// due to VC this cannot be in the header file :(
const static std::string m_configurationOptions[4] = {
	"textures",
	"meshes",
	"skyboxes",
	"materials"
};

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
			}else if( 0 == configContext.compare("meshes") ){
				LoadMesh(line);
			}else if( 0 == configContext.compare("skyboxes") ){
				LoadCubeTexture(line);
			}else if( 0 == configContext.compare("materials") ){
				LoadMaterial(line);
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
	LOG(DEBUG) << "[PRELOAD] Loading texture: " << pathToFile;
	m_textureMap[pathToFile] = new Texture(pathToFile);
}

void Loader::LoadCubeTexture(std::string pathToFile){
	LOG(DEBUG) << "[PRELOAD] Loading CubeMap texture: " << pathToFile;
	m_cubeTextureMap[pathToFile] = new CubeTexture(pathToFile);
}

void Loader::LoadMesh(std::string pathToFile){
	LOG(DEBUG) << "[PRELOAD] Loading mesh: " << pathToFile;
	m_meshMap[pathToFile] = new Mesh(pathToFile);
}

void Loader::LoadMaterial(std::string pathToFile){
	LOG(DEBUG) << "[PRELOAD] Loading material: " << pathToFile;
	
	std::string materialFile = LoadFileContent(pathToFile);

	float emissive = 0;
	float shiny = 0;
	float density = 0;
	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;

	std::string mtlname;

	std::stringstream materialStream(materialFile);
	std::string line;

	char removeCharacterList[] = " []";

	while( std::getline(materialStream, line, '\n') ){

		// ignore empty and comments
		if(line.empty() || line.find("#") == 0 ){
			continue;
		}

		std::string token; 
		std::stringstream stream(line);

		stream >> token;

		if( token.compare("e") == 0 ){
			stream >> emissive;
		}else if( token.compare("Ka") == 0 ){
			stream >> ambient.r >> ambient.g >> ambient.b;
		}else if( token.compare("Kd") == 0 ){
			stream >> diffuse.r >> diffuse.g >> diffuse.b;
		}else if( token.compare("Ks") == 0 ){
			stream >> specular.r >> specular.g >> specular.b;
		}else if( token.compare("Ns") == 0 ){
			stream >> shiny;
		}else if( token.compare("newmtl") ){
			stream >> mtlname;
		}else if( token.compare("Ni") == 0 ){
			stream >> density;
		}else if( stream.fail() == true ){
			LOG(DEBUG) << "unset token:" << token; 
		}
	}

	Material* mat = new Material();
	
	mat->SetName(mtlname);

	mat->SetDiffuse(diffuse);
	mat->SetAmbient(ambient);
	mat->SetSpecular(specular);
	mat->SetEmissive(glm::vec4(emissive));
	mat->SetDensity(density);
	mat->SetShiny(shiny);

	m_materialMap[pathToFile] = mat;

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
	if( m_materialMap.find(key) != m_materialMap.end() ){
		return m_materialMap.at(key);
	}

	LOG(ERROR) << "Material " << key << " not found";
}

bool Loader::MeshExists(std::string key){
	return m_meshMap.find(key) != m_meshMap.end();
}

bool Loader::TextureExists(std::string key){
	return m_textureMap.find(key) != m_textureMap.end();

}

bool Loader::MaterialExists(std::string key){
	return m_materialMap.find(key) != m_materialMap.end();
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