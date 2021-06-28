#include <ESP8266WiFi.h>
#include <PubSubClient.h>

// WiFi
const char *ssid = "TE-Data";	// Enter your WiFi name
const char *password = "5506415emileshack"; // Enter WiFi password

// MQTT Broker
const char *mqtt_broker = "r6470512.us-east-1.emqx.cloud";
const char *topic = "alcohol_density";
const char *mqtt_username = "NodeMCU";
const char *mqtt_password = "1998";
const char *client_id = "node-mcu";
const int mqtt_port = 15881;

WiFiClient espClient;
PubSubClient client(espClient);

void setup()
{
	// Set software serial baud to 115200;
	Serial.begin(115200);
	WiFi.begin(ssid, password);
	while (WiFi.status() != WL_CONNECTED)
	{
		delay(500);
		Serial.println("Connecting to WiFi..");
	}
	Serial.println("Connected to the WiFi network");
	client.setServer(mqtt_broker, mqtt_port);
	// client.setCallback(callback);
	while (!client.connected())
	{
		Serial.printf("The client %s connects to the public mqtt broker\n", client_id);
		if (client.connect(client_id, mqtt_username, mqtt_password))
		{
			Serial.println("Public emqx mqtt broker connected");
		}
		else
		{
			Serial.print("failed with state ");
			Serial.print(client.state());
			delay(2000);
		}
	}
}

// void callback(char *topic, byte *payload, unsigned int length)
// {
// 	Serial.print("Message arrived in topic: ");
// 	Serial.println(topic);
// 	Serial.print("Message:");
// 	for (int i = 0; i < length; i++)
// 	{
// 		Serial.print((char)payload[i]);
// 	}
// 	Serial.println();
// 	Serial.println("-----------------------");
// }

void loop()
{
	client.publish(topic, random(50)+"");
	delay(random(500, 2000));
	client.loop();
}