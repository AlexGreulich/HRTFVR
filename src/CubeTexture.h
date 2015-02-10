#ifndef HRTFVR_CUBE_TEXTURE_H
#define HRTFVR_CUBE_TEXTURE_H

#include <string>
#include <GL/glew.h>
#include "Texture.h"

class CubeTexture : public Texture{
public:
	CubeTexture(std::string pathToFile);
	void Bind();
	~CubeTexture();
protected:
	void CreateTexture();
};

#endif