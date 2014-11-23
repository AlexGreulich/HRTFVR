
#include "OculusHandler.h"


//include Oculus SDK
#include "OVR_CAPI.h"


// Choose whether the SDK performs rendering/distortion, or the application. 
#define          SDK_RENDER 1  //Do NOT switch until you have viewed and understood the Health and Safety message.
//Disabling this makes it a non-compliant app, and not suitable for demonstration. In place for development only.
const bool       FullScreen = true; //Should be true for correct timing.  Use false for debug only.

ovrHmd hmd;

OculusHandler::OculusHandler()
{
}

bool OculusHandler::initialize(){
	bool riftConnected = false;
	ovr_Initialize();
	hmd = ovrHmd_Create(0);
	if (hmd){
		riftConnected = true;

		// Get more details about the HMD.
		ovrSizei resolution = hmd->Resolution;

		// Do something with the HMD.
	}
	return riftConnected;
}

void OculusHandler::destroyHMD(){
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();
}

OculusHandler::~OculusHandler()
{
}
