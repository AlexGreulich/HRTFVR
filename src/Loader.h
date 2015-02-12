#ifndef HRTFVR_LOADER_H
#define HRTFVR_LOADER_H

#include "Logger.h"
#include "Mesh.h"
#include "Texture.h"
#include "CubeTexture.h"
#include "Material.h"
#include <string>
#include <sstream>

#define PRELOAD_FILE_PATH "resources/preload.conf"

class Loader{

public:
	Loader();

	static std::string LoadFileContent(const char* pathToFile);
	static std::string LoadFileContent(std::string pathToFile);

	// loader
	void LoadTexture(std::string pathToFile);
	void LoadMesh(std::string pathToFile);
	void LoadMaterial(std::string pathToFile);
	void LoadCubeTexture(std::string pathToFile);

	// exists 
	bool MeshExists(std::string key);
	bool TextureExists(std::string key);
	bool MaterialExists(std::string key);

	// getter
	Mesh* GetMesh(std::string key);
	Texture* GetTexture(std::string key);
	Material* GetMaterial(std::string key);

	virtual ~Loader();

protected:

	// preloader config options
	//const static std::string m_configurationOptions[4];

	std::map<std::string, Mesh*> m_meshMap;
	std::map<std::string, Texture*> m_textureMap;
	std::map<std::string, CubeTexture*> m_cubeTextureMap;
	std::map<std::string, Material*> m_materialMap;

	// utility
	bool IsConfigContext(std::string* configLine);

	// bootstraps preload process
	void Preload();


};

#endif