#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <MQTTClient.h> 
#include <ArduinoJson.h>
#include "pin_definitions.h"
#include "mqtt_data.h"
#include "../../.cred/secrets.h"


// MQTT Server
extern long lastMsg;
extern char msg[50];
extern int value;
extern WiFiClientSecure net; //
extern MQTTClient client; //

// Functions
void mqttSetup();
void mqttLoop();
// void callback(char* topic, byte* message, unsigned int length);
void reconnect();
void publishMessage();
void connectAWS();

#endif