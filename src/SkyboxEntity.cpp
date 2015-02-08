#ifndef HRTFVR_SKYBOX_ENTITY_CPP
#define HRTFVR_SKYBOX_ENTITY_CPP

#include "SkyboxEntity.h"

SkyboxEntity::SkyboxEntity(){

	float[108] VERTICES = {        
	    -m_size,  m_size, -m_size,
	    -m_size, -m_size, -m_size,
	    m_size, -m_size, -m_size,
	     m_size, -m_size, -m_size,
	     m_size,  m_size, -m_size,
	    -m_size,  m_size, -m_size,

	    -m_size, -m_size,  m_size,
	    -m_size, -m_size, -m_size,
	    -m_size,  m_size, -m_size,
	    -m_size,  m_size, -m_size,
	    -m_size,  m_size,  m_size,
	    -m_size, -m_size,  m_size,

	     m_size, -m_size, -m_size,
	     m_size, -m_size,  m_size,
	     m_size,  m_size,  m_size,
	     m_size,  m_size,  m_size,
	     m_size,  m_size, -m_size,
	     m_size, -m_size, -m_size,

	    -m_size, -m_size,  m_size,
	    -m_size,  m_size,  m_size,
	     m_size,  m_size,  m_size,
	     m_size,  m_size,  m_size,
	     m_size, -m_size,  m_size,
	    -m_size, -m_size,  m_size,

	    -m_size,  m_size, -m_size,
	     m_size,  m_size, -m_size,
	     m_size,  m_size,  m_size,
	     m_size,  m_size,  m_size,
	    -m_size,  m_size,  m_size,
	    -m_size,  m_size, -m_size,

	    -m_size, -m_size, -m_size,
	    -m_size, -m_size,  m_size,
	     m_size, -m_size, -m_size,
	     m_size, -m_size, -m_size,
	    -m_size, -m_size,  m_size,
	     m_size, -m_size,  m_size
	};

	CubeTexture texture();

}

SkyboxEntity::~SkyboxEntity(){
	
}

#endif