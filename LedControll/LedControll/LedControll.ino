/*
 Name:		LedControll.ino
 Created:	6/12/2017 3:46:57 PM
 Author:	Jonas
*/

// the setup function runs once when you press reset or power the board
#include "IMode.h"
#include "Color.h"
#include "LedStrip.h"

LedStrip ledStrip1;

void setup() {
	ledStrip1 = LedStrip(9, 10, 11, 255, 130, 140);
	ledStrip1.changeColor(Color(255, 0, 0));
}

// the loop function runs over and over again until power down or reset
void loop() {
	ledStrip1.write();
}
