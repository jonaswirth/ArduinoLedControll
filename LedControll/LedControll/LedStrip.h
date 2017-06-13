// LedStrip.h

#ifndef _LEDSTRIP_h
#define _LEDSTRIP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "Color.h"
class LedStrip {
private:
	int redPin;
	int greenPin;
	int bluePin;
	int maxRed;
	int maxGreen;
	int maxBlue;
	Color color;
public:
	LedStrip();
	LedStrip(int r, int g, int b, int maxR, int maxG, int maxB);
	void changeColor(Color newColor);
	void shine();
};

#endif

