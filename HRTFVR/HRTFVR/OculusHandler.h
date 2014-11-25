#pragma once

//include Oculus SDK
#include "OVR_CAPI.h"

class OculusHandler
{
public:
	OculusHandler();
	~OculusHandler();

	

	bool initialize();
	void destroyHMD();

private: 
	

};

