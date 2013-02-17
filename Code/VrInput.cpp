
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
	VRIO_Message m;
	angle.Set(0,0,0);

	if (_initialized && _vrClient->getChannelCount() > 0)
	{
		_vrClient->getOrientation(HEAD, m);
		angle.Set(m.pitch, m.yaw, m.roll);
	}
}