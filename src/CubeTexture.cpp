#ifndef HRTFVR_CUBE_TEXTURE_CPP
#define HRTFVR_CUBE_TEXTURE_CPP

#include "CubeTexture.h"
#include "Logger.h"
#include "stb_image.h"

CubeTexture::CubeTexture(std::string path):
Texture(){

	glGenTextures(1, &m_texture);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	// 
	// path points to a directory containing 6 files: 0.png, 1.png[...],
	// each one represents one side of a cube:
	// 
	// 0 := right face
	// 1 := left face
	// 2 := top face
	// 3 := bottom face
	// 4 := back face
	// 5 := front face
	// 
	// 
	for( int i = 0; i < 6; i++ ){

		std::string filePath = path + std::to_string(i) + std::string(".png");

		// LoadTexture loads the texture file
		// this method sets:
		// - m_data
		// - m_width
		// - m_height
		Texture::LoadTexture( filePath );
		
		glTexImage2D(
			GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
			0,
			GL_RGBA,
			m_width,
			m_height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			m_data
		);

		DestroyTextureData();

	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

}

void CubeTexture::Bind(){
	LOG(DEBUG) << "using TEXTURE CUBE_MAP";
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
}

CubeTexture::~CubeTexture(){

}

#endif