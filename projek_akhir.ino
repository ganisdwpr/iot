#include <ESP8266WiFi.h>
#include "ThingSpeak.h"

//Replace your wifi credentials here
const char* ssid     = "Assalamualaikum";
const char* password = "alwaysallah";

//change your channel number here
//https://thingspeak.com/channels/1302871
unsigned long channel = 1302871;

//2,3 and 4 are channel fields in thingspeak.
unsigned int led1 = 2;
unsigned int led2 = 3;

WiFiClient  client;


void setup() {
  Serial.begin(115200);
  delay(100);

  pinMode(D1, OUTPUT);
  pinMode(D8, OUTPUT);
  digitalWrite(D1, 0);
  digitalWrite(D8, 0);
  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.print("Netmask: ");
  Serial.println(WiFi.subnetMask());
  Serial.print("Gateway: ");
  Serial.println(WiFi.gatewayIP());
  ThingSpeak.begin(client);

}


void loop() {

  //get the last data of the fields
  int led_1 = ThingSpeak.readFloatField(channel, led1);
  int led_2 = ThingSpeak.readFloatField(channel, led2);

  if(led_1 == 1){
    digitalWrite(D1, 1);
    Serial.println("Lampu Ruang Tengah Nyala..!");
  }
  else if(led_1 == 0){
    digitalWrite(D1, 0);
    Serial.println("Lampu Ruang Tengah Mati..!");
  }

  if(led_2 == 1){
    digitalWrite(D8, 1);
    Serial.println("Lampu Kamar Nyala..!");
  }
  else if(led_2 == 0){
    digitalWrite(D8, 0);
    Serial.println("Lampu Kamar Mati..!");
  }

 
  Serial.println(led_1);
  Serial.println(led_2);
  delay(5000);

}
