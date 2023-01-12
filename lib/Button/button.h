#ifndef _Button_H_
#define _Button_H_

#include <Arduino.h>
#include "../MQTT/mqtt.h"
#include "pin_definitions.h"

// Variables
  extern int buttonState;  // variable for reading the pushbutton status

  // Variables for ensuring that the button is not pressed more than once within a second.
  extern bool buttonPressed;
  extern int interval;
  extern long lastTime;

// Functions
void buttonLoop();

#endif