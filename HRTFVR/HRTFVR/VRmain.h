#pragma once

#include "OculusHandler.h"
#include "SceneManager.h"
#include "Renderer.h"
class VRmain{
public:
	VRmain();
	~VRmain();
	OculusHandler* oculus;
	SceneManager* sceneManager;
	Renderer* renderer;

private: 
	bool useRift;
	
	void init();
	void destroyAndCleanse();
	

};

