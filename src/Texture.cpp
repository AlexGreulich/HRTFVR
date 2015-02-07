#ifndef HRTFVR_TEXTURE_CPP
#define HRTFVR_TEXTURE_CPP

#include "Texture.h"
#include "stb_image.c"
#include <iostream>

Texture::Texture(const std::string fileName):
m_texture(0)
{
	int width, height, numComponents;
	unsigned char* data = stbi_load((fileName).c_str(), &width, &height, &numComponents, 4);

	if (data == NULL){
		std::cerr << "Error: Unable to load texture: " << fileName << std::endl;
		stbi_image_free(data);
		return;
	}
		

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	stbi_image_free(data);
}

void Texture::Bind()
{
	if (m_texture != 0){
		glBindTexture(GL_TEXTURE_2D, m_texture);
	}
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

#endif