#ifndef HRTFVR_SKYBOX_ENTITY_H
#define HRTFVR_SKYBOX_ENTITY_H

#include "Entity.h"
#include "CubeTexture.h"

class SkyboxEntity : public Entity{

public:
	SkyboxEntity();
	virtual ~SkyboxEntity();

protected:

	float m_size;

	// texture, mesh, transform	

};

#endif