// 
// 
// 

#include "Potentiometer.h"

Potentiometer::Potentiometer(int port) {
	analogPort = port;
}

int Potentiometer::read() {
	smoothValue = 0.6 * smoothValue + 0.4 * analogRead(analogPort);
	oldValue = smoothValue;
	return map(smoothValue, 0, 1023, 0, 255);
	
}
