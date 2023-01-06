#include <Arduino.h>
#include <mqtt.h>
#include <button.h>
#include <wifi_setup.h>
#include "pin_definitions.h"


void setup() {

  // Initialize Serial Communications:
  Serial.begin(115200);
  // Initialize the LED and Button Pins:
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT);

  setup_wifi();
  mqttSetup();
}

void loop() {
  mqttLoop();
  buttonLoop();
}


