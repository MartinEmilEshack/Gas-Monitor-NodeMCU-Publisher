#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>

#define WIFI_SSID "Daabiss"
#define WIFI_PASSWORD "         "
int sensorValue;

void setup()
{
	Serial.begin(115200);
	delay(500);
	// Connect to Wi-Fi
	Serial.print("Wi-Fi...");
	WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
	Serial.print("Connecting...");
	while (WiFi.status() != WL_CONNECTED)
	{
		Serial.print(".");
		delay(500);
	}
	Serial.println("");
	Serial.print("Successfully connected to : ");
	Serial.println(WIFI_SSID);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
	Serial.println();
}

void loop()
{
	getMeasure();
	sendValue(sensorValue);
	delay(500);
}

void getMeasure()
{
	sensorValue = analogRead(A0);
	Serial.println(sensorValue);
	delay(1);
}

void sendValue(String data)

{
	if (WiFi.status() == WL_CONNECTED)
	{
		HTTPClient http;
		String url = "http://localhost:4000/api/alcohol?alcohol=" + data;
		http.begin(url);
		http.addHeader("Content-Type", "application/json");
		//int httpResponseCode = http.POST("{\"alcohol\": \""+data+"\"}");

		int httpCode = http.GET();
		Serial.println("httpCode: " + String(httpCode));
		if (httpCode > 0)
		{
			String payload = http.getString();
			Serial.println(payload);
			if (payload[0] == "HTTP/1.1 200 OK")
			{
				Serial.println("Value Sent successfully");
			}
			else
			{
				Serial.println("Value wasn't Sent successfully");
			}
		}
		else
		{
			Serial.print("Error code: ");
			Serial.println(httpCode);
		}

		http.end();
	}

	else //Not connected to internet
	{
		Serial.println("Internet Problem!");
	}
}

} //end of loop
