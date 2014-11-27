
#include "OculusHandler.h"
#include <OVR_Math.h>// Math helper 
#include <iostream>
// Choose whether the SDK performs rendering/distortion, or the application. 
#define          SDK_RENDER 1  //Do NOT switch until you have viewed and understood the Health and Safety message.
//Disabling this makes it a non-compliant app, and not suitable for demonstration. In place for development only.
const bool       FullScreen = true; //Should be true for correct timing.  Use false for debug only.

ovrHmd hmd;

using namespace OVR;
using namespace std;
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
		hmdResolution.w = hmd->Resolution.w;
		hmdResolution.h = hmd->Resolution.h;
		camFrustumHFov = hmd->CameraFrustumHFovInRadians;// The horizontal FOV of the position tracking camera frustum.
		camFrustumVFov = hmd->CameraFrustumVFovInRadians;// The vertical FOV of the position tracking camera frustum.
		camFrustumNearZ = hmd->CameraFrustumNearZInMeters;// The distance from the position tracking camera to the near frustum bounds.
		camFrustumFarZ = hmd->CameraFrustumFarZInMeters;

		trackingcaps = hmd->TrackingCaps;
		hmdCaps = hmd->HmdCaps;
		distortionCaps = hmd->DistortionCaps;

		eyeFov[0] = hmd->DefaultEyeFov[0];
		eyeFov[1] = hmd->DefaultEyeFov[1];
		maxEyeFov[0] = hmd->MaxEyeFov[0];
		maxEyeFov[1] = hmd->MaxEyeFov[1];
		eyeRenderOrder[0] = hmd->EyeRenderOrder[0];
		eyeRenderOrder[1] = hmd->EyeRenderOrder[1];

		deviceName = hmd->DisplayDeviceName;
		displayID = hmd->DisplayId;

		// now for the sensor init:
		ovrHmd_ConfigureTracking(
			hmd, ovrTrackingCap_Orientation |
			ovrTrackingCap_MagYawCorrection |
			ovrTrackingCap_Position, 0);
			//these are tracking capability flags; 0 is for required Capabilities
			// so we get the caps of the DK2 or none 

		trackingState = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
		
	}
	else{
		// we can use a simulated HMD to test and debug tracking and render code
		//hmd = ovrHmd_CreateDebug(ovrHmd_DK2);

		// set up fake sensor data here
	}
	return riftConnected;
}

void OculusHandler::updateTracking(){
	if (hmd){
		frameTiming = ovrHmd_BeginFrameTiming(hmd, 0);

		trackingState = ovrHmd_GetTrackingState(hmd, ovr_GetTimeInSeconds());
		if (trackingState.StatusFlags & (ovrStatus_OrientationTracked | ovrStatus_PositionTracked)); {
			// get trackingpose here

			Posef pose = trackingState.HeadPose.ThePose;
			pose.Rotation.GetEulerAngles<Axis_Y, Axis_X, Axis_Z>(&yaw, &pitch, &roll);


			cout << "yaw: " << RadToDegree(yaw) << endl;
			cout << "pitch: " << RadToDegree(pitch) << endl;
			cout << "roll: " << RadToDegree(roll) << endl;

		}
		ovrHmd_EndFrameTiming(hmd);
	}
}

void OculusHandler::destroyHMD(){
	ovrHmd_Destroy(hmd);
	ovr_Shutdown();
}

OculusHandler::~OculusHandler()
{
	destroyHMD();
}
