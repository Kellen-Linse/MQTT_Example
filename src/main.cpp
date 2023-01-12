#include <Arduino.h>
#include <button.h>
#include <wifi_setup.h>
#include "pin_definitions.h"
#include "../lib/MQTT/mqtt.h"


void setup() {

  // Initialize Serial Communications:
  Serial.begin(115200);

  // Initialize the LED and Button Pins:
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);
  
  // Initialize WiFi and MQTT
  wifiSetup();
  mqttSetup();
}

void loop() {

  // Loops
  mqttLoop();
  buttonLoop();
}


