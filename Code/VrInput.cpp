
#include "StdAfx.h"
#include "vr_io.h"
#include "VrInput.h"

IVRIOClient* _vrClient;  
VrInput *g_vr = 0;

VrInput::VrInput()
{
	_vrClient = _vrio_getInProcessClient();	
	_vrClient->initialize();
	
	CryLogAlways("VR client initialized with %d channels", _vrClient->getChannelCount());
	g_vr = this;
	_initialized = true;
}

VrInput::~VrInput()
{
	_vrClient->dispose();
}

void VrInput::getHeadOrientation(Ang3 &angle)
{
	angle.Set(0,0,0);

}