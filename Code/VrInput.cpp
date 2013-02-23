
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
	_weaponCalibration(0,0,0);
	
	_prevYaw = 0;
	_prevWeaponYaw = 0;
	_accumulatedHeadYaw = 0;
	_accumulatedWeaponYaw = 0;

	g_vr = this;
	_initialized = true;	
}

VrInput::~VrInput()
{
	shutDown();
}

void VrInput::headOrientation(Ang3 &angle)
{
	angle.Set(DEG2RAD(-_headAngle.x), DEG2RAD(_headAngle.z), DEG2RAD(_headAngle.y));
}


float VrInput::headRoll()
{
	// THIS IS NEVER USED ANY MORE..... 
	return -99999999;
}

bool VrInput::trackingWeapon()
{
	return _vrClient->getChannelCount() > 1;
}

void VrInput::weaponOrientation(Ang3 &angle)
{
	// Reorienting to engine standards for angles
	angle.Set(DEG2RAD(-_weaponAngle.x), DEG2RAD(_weaponAngle.z), DEG2RAD(_weaponAngle.y));
}

void VrInput::update(float baseEngineYaw)
{
	VRIO_Message m;
	_headAngle.Set(0,0,0);

	// everything in the backend is currently using degrees.
	baseEngineYaw = RAD2DEG(baseEngineYaw);

	if (!_initialized || _vrClient->getChannelCount() == 0)
		return;
	
	// HEAD ANGLES
	_vrClient->getOrientation(HEAD, m);
	_headAngle.Set(m.pitch, m.yaw, m.roll);
	
	float deltaYaw = _headAngle.y - _prevYaw;
	_prevYaw = _headAngle.y;
	_accumulatedHeadYaw += deltaYaw;
	_headAngle.y = deltaYaw + baseEngineYaw;

	_headAngle -= _headCalibration;
	
	//WEAPON ANGLES
	if (!trackingWeapon())
		return;

	_vrClient->getOrientation(WEAPON, m);
	_weaponAngle.Set(m.pitch, m.yaw, m.roll);
	
	deltaYaw = _weaponAngle.y - _prevWeaponYaw;
	_prevWeaponYaw = _weaponAngle.y;
	_accumulatedWeaponYaw += deltaYaw;
	
	_weaponAngle.y = (baseEngineYaw - _accumulatedHeadYaw) + _accumulatedWeaponYaw;

	// CryLogAlways("weapon yaw: %f = baseyaw: %f - accumheadyaw: %f + accumweaponyaw: %f", _weaponAngle.y, baseEngineYaw, _accumulatedHeadYaw, _accumulatedWeaponYaw);

	_weaponAngle -= _weaponCalibration;

	_prevEngineYaw = baseEngineYaw;
}

void VrInput::shutDown()
{
	if (_initialized)
		_vrClient->dispose();
}

void VrInput::calibrate()
{
	_headCalibration = Ang3(_headAngle + _headCalibration);
	_headCalibration.y = 0; // no head yaw calibration
	_weaponCalibration = Ang3(_weaponAngle + _weaponCalibration);
	centerWeapon();
}

void VrInput::centerWeapon()
{
		
	VRIO_Message head, weapon;
	_vrClient->getOrientation(HEAD, head);
	_vrClient->getOrientation(WEAPON, weapon);

	_weaponCalibration.y = weapon.yaw - head.yaw;
}
