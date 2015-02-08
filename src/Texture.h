#ifndef TEXTURE_H
#define TEXTURE_H

#include <string>
#include <GL/glew.h>

class Texture
{
public:
	Texture();
	Texture(const std::string fileName);
	void Bind();
	virtual ~Texture();
	void LoadTexture(std::string fileName);

protected:
	void CreateTexture();
	void DestroyTextureData();

	GLuint m_texture;
	int m_width;
	int m_height;
	unsigned char* m_data;
	
};

#endif