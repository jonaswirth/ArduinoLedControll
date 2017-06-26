/*
 Name:		LedControll.ino
 Created:	6/12/2017 3:46:57 PM
 Author:	Jonas Wirth
*/


#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "Color.h"
#include "LedStrip.h"

//Config
Color bestColors[] = { Color(255, 0, 0), Color(0, 255, 0), Color(0,0,255) };
int delayTime = 500;

//Led Strips
LedStrip ledStrip1;
int colorIndex = 0;

//Network
const char* ssid = "";
const char* pw = "";
ESP8266WebServer server(80);

// the setup function runs once when you press reset or power the board
void setup() {
	ledStrip1 = LedStrip(D6, D7, D8, 255, 130, 140);
	ledStrip1.changeColor(Color(255, 0, 0));
	WiFi.begin(const_cast<char*>(ssid), pw);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
	}

	//Register routes
	server.on("/changecolor", []() {
		server.send(200, "text/plain", "color changed");
		changeColor(getArgValue("address"), getArgValue("r"), getArgValue("g"), getArgValue("b"));
	});

	server.on("/setmode", []() {
		//Set the current mode of a strip, not implemented
	});

	server.on("setstate", []() {
		//Turn a strip on or off, not implmeted
	});

	server.onNotFound([] {
		server.send(404, "text/plain", "The requested action could not be found!");
	});

	server.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	server.handleClient();
	ledStrip1.shine();
}

int getArgValue(String name)
{
	for (uint8_t i = 0; i < server.args(); i++)
		if (server.argName(i) == name)
			return server.arg(i).toInt();
	return -1;
}

void next() {
	ledStrip1.changeColor(bestColors[colorIndex]);
	colorIndex++;
	if (colorIndex >= 2) {
		colorIndex = 0;
	}
	delay(delayTime);
}

void changeColor(int address, int red, int green, int blue) {
	//Currently there is only one led strip so the address is irrelevant
	ledStrip1.changeColor(Color(red, green, blue));
}
