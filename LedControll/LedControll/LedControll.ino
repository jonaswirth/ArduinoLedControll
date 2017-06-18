/*
 Name:		LedControll.ino
 Created:	6/12/2017 3:46:57 PM
 Author:	Jonas
*/

// the setup function runs once when you press reset or power the board
#include "Color.h"
#include "LedStrip.h"
#include <ESP8266WiFi.h>
#include <ArduinoHttpServer.h>
//Config
Color bestColors[] = { Color(255, 0, 0), Color(0, 255, 0), Color(0,0,255) };
int delayTime = 500;

//Led Strips
LedStrip ledStrip1;
int colorIndex = 0;

//Network
const char* ssid = "";
const char* pw = "";
WiFiServer wifiServer(80);


void setup() {
	ledStrip1 = LedStrip(D6, D7, D8, 255, 130, 140);
	ledStrip1.changeColor(Color(255, 0, 0));
	WiFi.begin(const_cast<char*>(ssid), pw);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
	}
	wifiServer.begin();
}

// the loop function runs over and over again until power down or reset
void loop() {
	WiFiClient client(wifiServer.available());
	if (client.connected())
	{
		// Connected successfully to client. Initialize StreamHttpRequest object.
		ArduinoHttpServer::StreamHttpRequest<1023> httpRequest(client);

		// Parse the request.
		if (httpRequest.readRequest())
		{
			// Parsing the request. A request url contains action/address/value
			String action = httpRequest.getResource()[0];
			String address = httpRequest.getResource()[1];
			String value = httpRequest.getResource()[2];

			// Retrieve HTTP method.
			ArduinoHttpServer::MethodEnum method(ArduinoHttpServer::MethodInvalid);
			method = httpRequest.getMethod();

			if (method == ArduinoHttpServer::MethodGet)
			{
				if (action.equals("changecolor")) {
					changeColor(address, value);
				}
				ArduinoHttpServer::StreamHttpReply httpReply(client, httpRequest.getContentType());
				httpReply.send("OK");
			}

		}
		else
		{
			// Error handling
			ArduinoHttpServer::StreamHttpErrorReply httpReply(client, httpRequest.getContentType());
			httpReply.send(httpRequest.getErrorDescrition());
		}
	}
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

void changeColor(String address, String color) {
	String colors[3];
	char c[12];
	color.toCharArray(c, 12);
	int i = 0;
	char *ch;
	ch = strtok(c, ";");
	while (ch != NULL) {
		colors[i] = ch;
		ch = strtok(NULL, ";");
		i++;
	}
	ledStrip1.changeColor(Color(colors[0].toInt(), colors[1].toInt(), colors[2].toInt()));
}
