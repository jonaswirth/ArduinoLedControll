/*
 Name:		LedControll.ino
 Created:	6/12/2017 3:46:57 PM
 Author:	Jonas Wirth
*/

#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "Color.h"
#include "LedStrip.h"


//Config
String bridgeAddress = "192.168.178.63:50136";
int deviceId = 1;

Color bestColors[] = { Color(255, 0, 0), Color(0, 255, 0), Color(0,0,255) };
int delayTime = 500;

//Modes
enum Mode {Shine, Blink, Pulse, Fade, FadeAll};
Mode currentMode;

//Led Strips
LedStrip ledStrip1;
int colorIndex = 0;

//Network
const char* ssid = "";
const char* pw = "";
ESP8266WebServer server(80);
ESP8266WiFiMulti wifiMulti;

HTTPClient httpClient;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, LOW);
	//Setup timer
	ledStrip1 = LedStrip(D7, D8, D6, 255, 130, 140);
	ledStrip1.changeColor(Color(255, 0, 0));

	//Register to bridge
	wifiMulti.addAP(ssid, pw);
	bool ready = false;
	while (ready != true) {
		digitalWrite(BUILTIN_LED, HIGH);
		if ((wifiMulti.run() != true)) {
			httpClient.begin("http://" + bridgeAddress + "/api/device/register?id=" + deviceId);
			int responseCode = httpClient.GET();
			if (responseCode > 0) {
				ready = true;
			}
			httpClient.end();
		}
		delay(250);
		digitalWrite(BUILTIN_LED, LOW);
		delay(250);
	}

	//Register routes
	server.on("/changecolor", []() {
		server.send(200, "text/plain", "color changed");
		changeColor(getArgValue("address"), getArgValue("r"), getArgValue("g"), getArgValue("b"));
	});

	server.on("/setmode", []() {
		currentMode = (Mode)getArgValue("mode");
	});

	server.on("/setstate", []() {
		ledStrip1.changeColor(Color(0, 0, 0));
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
