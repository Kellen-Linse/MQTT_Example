#include "button.h"

// Button & LED
   int buttonState = LOW;  // variable for reading the pushbutton status

  // Variables for ensuring that the button is not pressed more than once within a second.
    bool buttonPressed = false;
    long lastTime = 0;

void buttonLoop(){
    buttonState = digitalRead(buttonPin); // read the state of the pushbutton value.
  long timeNow = millis(); // Get the current time.

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    // digitalWrite(ledPin, HIGH);

    if(!buttonPressed){
      if(timeNow - lastTime > 1000){
        lastTime = millis();
        Serial.println("Pressed");
        client.publish("Kellen_esp32/test", "Button Pressed");
        buttonPressed = true;
      }
    }   
  } else {
    // turn LED off:
    // digitalWrite(ledPin, LOW);
    buttonPressed = false;
  }
}

