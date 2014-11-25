
#include "OculusHandler.h"
#include <OVR_Math.h>	// Math helper 



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
			
		// I left out the serialID of the device, maybe needed
		ovrSizei resolution = hmd->Resolution;
		float camFrustumHFov = hmd->CameraFrustumHFovInRadians;// The horizontal FOV of the position tracking camera frustum.
		float camFrustumVFov = hmd->CameraFrustumVFovInRadians;// The vertical FOV of the position tracking camera frustum.
		float camFrustumNearZ = hmd->CameraFrustumNearZInMeters;// The distance from the position tracking camera to the near frustum bounds.
		float camFrustumFarZ = hmd->CameraFrustumFarZInMeters;

		unsigned int trackingcaps = hmd->TrackingCaps;
		unsigned int hmdCaps = hmd->HmdCaps;
		unsigned int distortionCaps = hmd->DistortionCaps;

		ovrFovPort eyeFov[2] = { hmd->DefaultEyeFov[0], hmd->DefaultEyeFov[1] };
		ovrFovPort maxEyeFov[2] = { hmd->MaxEyeFov[0], hmd->MaxEyeFov[1] };
		ovrEyeType eyeRenderOrder[2] = { hmd->EyeRenderOrder[0], hmd->EyeRenderOrder[1] };
		
		const char* deviceName = hmd->DisplayDeviceName;
		int displayID = hmd->DisplayId;

		// now for the sensor init:
		ovrHmd_ConfigureTracking(
			hmd, ovrTrackingCap_Orientation |
			ovrTrackingCap_MagYawCorrection |
			ovrTrackingCap_Position, 0);
			//these are tracking capability flags; 0 is for required Capabilities
			// so we get the caps of the DK2 or none 

		ovrTrackingState tstate = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
		if (tstate.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)); {
			// get trackingpose here
		}
		/*
		Posef pose = tstate.HeadPose.ThePose;
		float yaw, float pitch, float roll;
		pose.Orientation.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &eyePitch, &eyeRoll);
		*/
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
