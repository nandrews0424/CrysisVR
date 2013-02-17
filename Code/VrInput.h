#ifndef __VRINPUT_H__
#define __VRINPUT_H__

#pragma once

#include "Cry_Vector3.h"

class VrInput
{

public:

	VrInput(void);
	~VrInput(void);

	void getHeadOrientation(Ang3 &angle);
	bool initialized() { return _initialized; }

private:
	bool _initialized;

};

extern VrInput *g_vr;


#endif 
