#pragma once

//include Oculus SDK
#include "OVR_CAPI.h"
#include "OVR_Math.h"

class OculusHandler
{
public:
	OculusHandler();
	~OculusHandler();

	//HMD data
	ovrHmdDesc hmdDescription;
	ovrSizei hmdResolution;
	float camFrustumHFov;
	float camFrustumVFov;
	float camFrustumNearZ;
	float camFrustumFarZ;

	unsigned int trackingcaps;
	unsigned int hmdCaps;
	unsigned int distortionCaps;

	ovrFovPort eyeFov[2];
	ovrFovPort maxEyeFov[2];
	ovrEyeType eyeRenderOrder[2];

	const char* deviceName;
	int displayID;
	
	ovrTrackingState trackingState;

	ovrFrameTiming frameTiming;

	float yaw;
	float pitch;
	float roll;

	bool initialize();
	void destroyHMD();

	void updateTracking();

private: 
	

};

