
#include "StdAfx.h"
#include "vr_io.h"
#include "VrInput.h"

IVRIOClient* _vrClient;  

VrInput::VrInput()
{
	_vrClient = _vrio_getInProcessClient();	


}

VrInput::~VrInput()
{
	_vrClient->dispose();
}

void VrInput::getHeadOrientation(Ang3 &angle)
{
	angle.Set(0,0,0);

}