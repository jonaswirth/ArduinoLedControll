// 
// 
// 

#include "LedStrip.h"
#include "Color.h"

LedStrip::LedStrip()
{
}

LedStrip::LedStrip(int r, int g, int b, int maxR, int maxG, int maxB)
{
	redPin = r;
	greenPin = g;
	bluePin = b;
	maxRed = maxR;
	maxGreen = maxG;
	maxBlue = maxB;

	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
}

void LedStrip::changeColor(Color newColor)
{
	color = newColor;
}

void LedStrip::write()
{
	writeColor(color);
}

void LedStrip::writeColor(Color clr) {
	analogWrite(redPin, map(clr.get_red(), 0, 255, 0, maxRed));
	analogWrite(greenPin, map(clr.get_green(), 0, 255, 0, maxGreen));
	analogWrite(bluePin, map(clr.get_blue(), 0, 255, 0, maxBlue));
}


