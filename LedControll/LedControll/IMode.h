// IMode.h

#ifndef _IMODE_h
#define _IMODE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class IMode
{
public:
	virtual void write();
};

#endif

