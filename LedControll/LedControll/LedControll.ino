/*
 Name:		LedControll.ino
 Created:	6/12/2017 3:46:57 PM
 Author:	Jonas
*/

// the setup function runs once when you press reset or power the board
#include "Color.h"
#include "LedStrip.h"
//Config
Color bestColors[] = { Color(255, 0, 0), Color(0, 255, 0), Color(0,0,255) };
int delayTime = 500;


LedStrip ledStrip1;
int colorIndex = 0;



void setup() {
	ledStrip1 = LedStrip(9, 10, 11, 255, 130, 140);
	ledStrip1.changeColor(Color(255, 0, 0));
}

// the loop function runs over and over again until power down or reset
void loop() {
	ledStrip1.shine();
	//next();
}

void next() {
	ledStrip1.changeColor(bestColors[colorIndex]);
	colorIndex++;
	if (colorIndex >= 2) {
		colorIndex = 0;
	}
	delay(delayTime);
}
