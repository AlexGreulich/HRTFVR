#ifndef HRTFVR_TERRAIN_H
#define HRTFVR_TERRAIN_H

#include "Entity.h"

class Terrain : public Entity{
public:
	Terrain();

	void Generate();

	virtual ~Terrain();

protected:
	const float SIZE = 800;
	const int VERTEX_COUNT = 128;

	float x;
	float y;

};

#endif