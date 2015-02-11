#ifndef HRTFVR_TEXTURE_CPP
#define HRTFVR_TEXTURE_CPP

#include "Texture.h"
#include "Logger.h"
#include "stb_image.c"
#include <iostream>

// empty constructor for derived classes
Texture::Texture(){}

Texture::Texture(const std::string fileName):
m_width(0),
m_height(0),
m_texture(0)
{
	LoadTexture(fileName);
	CreateTexture();
	DestroyTextureData();
}

void Texture::LoadTexture(std::string fileName){
	int numComponents;
	m_data = stbi_load((fileName).c_str(), &m_width, &m_height, &numComponents, 4);

	if (m_data == NULL){
		LOG(FATAL) << "Error: Unable to load texture: " << fileName << std::endl; 
		stbi_image_free(m_data);
		return;
	}
}

void Texture::CreateTexture(){
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri( GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE );
	
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
}

void Texture::DestroyTextureData(){
	stbi_image_free(m_data);
}

GLuint Texture::GetId(){
	return m_texture;
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_texture);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_texture);
}

#endif