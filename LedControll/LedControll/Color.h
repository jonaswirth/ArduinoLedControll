// Color.h

#ifndef _COLOR_h
#define _COLOR_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
class Color {
private:
	int red;
	int green;
	int blue;
public:
	Color();
	Color(int r, int g, int b);
	int get_red();
	int get_green();
	int get_blue();
};

#endif

