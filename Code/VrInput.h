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
	void weaponOrientation(Ang3 &angle);
	void update();
	void shutDown();
	void calibrate();
	void centerWeapon();

	bool initialized() { return _initialized; }
	bool trackingWeapon();

private:
	bool	_initialized;
	float	_prevYaw[10];
	float	_totalAccumulatedYaw[10];
	Ang3	_headAngle;
	Ang3	_headCalibration;
	Ang3	_weaponAngle;
	Ang3	_weaponCalibration;
};

extern VrInput *g_vr;


#endif 
