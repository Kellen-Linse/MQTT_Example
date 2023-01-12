#include "button.h"

// Variables
  int buttonState = LOW;

  // These variables are for ensuring that the button 
  // is not pressed more than once per second.
    bool buttonPressed = false;
    int interval = 1000;
    long lastTime = 0;

void buttonLoop(){
  buttonState = digitalRead(buttonPin); // Read the state of the pushbutton value.
  long timeNow = millis(); // Get the current time.

  // Check if the pushbutton is pressed. The buttonState is HIGH on pressed.
  if (buttonState == HIGH) {
    if(!buttonPressed){
      if(timeNow - lastTime > interval){
        lastTime = millis();
        Serial.println("Btn 1 pressed");
        publishMessage();
        buttonPressed = true;
      }
    }   
  } else {
    buttonPressed = false;
  }
}

