#pragma once

#include "OculusHandler.h"
class VRmain
{
public:
	explicit VRmain();
	~VRmain();
	OculusHandler* oculus;
	

private: 
	bool useRift;
	
	void init();
	void destroyAndCleanse();
	

};

