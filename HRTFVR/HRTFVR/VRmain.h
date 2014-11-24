#pragma once

#include "OculusHandler.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "InputHandler.h"
class VRmain{
public:
	VRmain();
	~VRmain();
	OculusHandler* oculus;
	SceneManager* sceneManager;
	Renderer* renderer;
	InputHandler* inputHandler;

private: 
	bool useRift;
	
	void init();
	void destroyAndCleanse();
	

};

