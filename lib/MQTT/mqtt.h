#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "pin_definitions.h"
#include "mqtt_data.h"

// MQTT Server
extern WiFiClient espClient;
extern PubSubClient client;
extern long lastMsg;
extern char msg[50];
extern int value;

// Functions
void mqttSetup();
void mqttLoop();
void callback(char* topic, byte* message, unsigned int length);
void reconnect();

#endif