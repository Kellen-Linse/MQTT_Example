#ifndef MQTT_H
#define MQTT_H

#include <Arduino.h>
#include <WiFiClientSecure.h>
#include <MQTTClient.h> 
#include <ArduinoJson.h>
#include "pin_definitions.h"
#include "mqtt_data.h"
#include "../../.cred/secrets.h"


// MQTT Server
extern WiFiClientSecure net;
extern MQTTClient client;

// Functions
void mqttSetup();
void mqttLoop();
void reconnect();
void publishMessage();
void connectAWS();

#endif