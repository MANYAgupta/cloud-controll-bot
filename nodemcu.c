#FOR NodeMCU:
#include <ESP8266WiFi.h> # importing library for NodeMCU
#include "MQTT.h" # importing library for cloud communication
#include <SoftwareSerial.h> # importing library for serial communication
SoftwareSerial s(D6,D5); # creating object for serial communication
const char ssid[] = "Himanshu"; # login credentials for Wi-Fi module
const char pass[] = "123456789";
WiFiClient net; # creating object for Wifi client
MQTTClient client; # creating object for Mqtt client
unsigned long lastMillis = 0;
void connect() {
Serial.print("checking wifi...");
while (WiFi.status() != WL_CONNECTED) { # checking whether Wi-Fi module
connected to hotspot
Serial.print(".");
delay(1000);
}
Serial.print("\nconnecting...");
while (!client.connect("")) {
Serial.print(".");
delay(1000);
}
Serial.println("\nconnected!");
client.subscribe("test1");
}
void messageReceived(String &topic, String &payload) {
s.print(payload);
Serial.println(payload);
}
void setup() {
s.begin(9600); # setting baud rate for serial communication
Serial.begin(115200); # setting baud rate for serial communication
WiFi.begin(ssid, pass); # beginning connection btw NodeMCU and
hotspot
client.begin("test.mosquitto.org", net); # interfacing NodeMCU with MQTT as broker
client.onMessage(messageReceived);
connect();
}
void loop() {
client.loop();
delay(10); // <- fixes some issues with WiFi stability
if (!client.connected()) {
connect();
}
}