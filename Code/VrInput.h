#ifndef __VRINPUT_H__
#define __VRINPUT_H__

#pragma once

#include "Cry_Vector3.h"

class VrInput
{

public:

	VrInput(void);
	~VrInput(void);

	void headOrientation(Ang3 &angle);
	float	headRoll();
	void weaponOrientation(Ang3 &angle);
	void update(float yawDelta);
	void shutDown();
	void calibrate();
	void centerWeapon();

	bool initialized() { return _initialized; }
	bool trackingWeapon();
	
private:
	bool	_initialized;
	float	_prevYaw;
	float	_prevEngineYaw;
	float	_prevWeaponYaw;
	float	_accumulatedHeadYaw;
	float	_accumulatedWeaponYaw;
	float	_totalAccumulatedYaw[10];

	float	_baseYaw; //accumulated engine yaw deltas from other inputs...

	Ang3	_headAngle;
	Ang3	_headCalibration;
	Ang3	_weaponAngle;
	Ang3	_weaponCalibration;
};

extern VrInput *g_vr;


#endif 
