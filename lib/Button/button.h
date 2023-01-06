#ifndef _Button_H_
#define _Button_H_

#include <Arduino.h>
#include <PubSubClient.h>
#include <mqtt.h>
#include "pin_definitions.h"

// Button & LED
extern int buttonState;  // variable for reading the pushbutton status

  // Variables for ensuring that the button is not pressed more than once within a second.
extern bool buttonPressed;
extern long lastTime;

void buttonLoop();

#endif