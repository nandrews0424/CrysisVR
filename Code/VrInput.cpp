
#include "StdAfx.h"
#include "vr_io.h"
#include "VrInput.h"

IVRIOClient* _vrClient;  
VrInput *g_vr = 0;

VrInput::VrInput()
{
	_vrClient = _vrio_getInProcessClient();	
	_vrClient->initialize();
	
	_headCalibration(0,0,0);
	
	_prevYaw = 0;

	g_vr = this;
	_initialized = true;	
}

VrInput::~VrInput()
{
	_vrClient->dispose();
}

void VrInput::headOrientation(Ang3 &angle)
{
	VRIO_Message m;
	angle.Set(0,0,0);

	if (_initialized && _vrClient->getChannelCount() > 0)
	{
		_vrClient->getOrientation(HEAD, m);
		angle.Set(m.pitch, m.yaw, m.roll);
	}
	
	angle -= _headCalibration;
	
	// A definite shitshow, but we never calibrate on yaw so the above doesn't matter
	float yawDelta = angle.y - _prevYaw;
	_prevYaw = angle.y;
	angle.y = yawDelta;
}


bool VrInput::trackingWeapon()
{
	return false;
}

void VrInput::weaponOrientation(Ang3 &angle)
{
	angle.Set(0,0,0);
}

void VrInput::update(float yawDelta)
{
	_baseYaw+=yawDelta;
	CryLogAlways("_baseYaw updated to: %f\n  (incr: %f)", _baseYaw, yawDelta);
}

void VrInput::shutDown()
{

}

void VrInput::calibrate()
{
	Ang3 headAngle;
	headOrientation(headAngle);
	_headCalibration = Ang3(headAngle + _headCalibration);
	_headCalibration.y;//yaw

}

void VrInput::centerWeapon()
{

}
