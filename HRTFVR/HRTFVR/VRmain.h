
#pragma once

#include "OculusHandler.h"
#include "SceneManager.h"
#include "Renderer.h"

class VRmain{
public:
	explicit VRmain();
	~VRmain();
	OculusHandler* oculus;
	SceneManager* sceneManager;
	Renderer* renderer; void init();

	
private:
	bool useRift;

	void destroyAndCleanse();


};

