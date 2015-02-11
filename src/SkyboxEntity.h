#ifndef HRTFVR_SKYBOX_ENTITY_H
#define HRTFVR_SKYBOX_ENTITY_H

#include <GL/glew.h>
#include "Entity.h"
#include "Texture.h"
#include "CubeTexture.h"

class SkyboxEntity : public Entity{

public:
	SkyboxEntity();
	SkyboxEntity(Mesh* mesh, CubeTexture* cubeTexture);
	void Draw();
	virtual ~SkyboxEntity();

protected:
};

#endif