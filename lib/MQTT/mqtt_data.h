#ifndef MQTT_DATA_H
#define MQTT_DATA_H

// MQTT Server
const char mqtt_server[100] = "broker.mqttdashboard.com";


// MQTT Port
const int mqtt_port = 1883;

// Client ID
const char clientID[20] = "Kellen_ESP32";

// Subscribe Topics
#define AWS_IOT_SUBSCRIBE_TOPIC "esp32/sub"

// Publish Topics
#define AWS_IOT_PUBLISH_TOPIC   "esp32/pub"

// Message for Publish Topics
const char msg_topic_1[100] = "Button Pressed";

#endif