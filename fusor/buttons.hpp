#pragma once

#include "pins.hpp"

int buttonType = 0;
int buttonValue  = 0;

void setup() {

  pinMode(SAFETY_SWITCH, INPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(FC, OUTPUT);
  digitalWrite(FC, HIGH); // FC needed for A0 to work???
}

void update() {

  buttonValue = analogRead(BUTTON_PIN);     // read the value from the sensor
  delay(50);

  if (buttonValue > 3300 && buttonValue < 3600) {
    Serial.println("Button 1 pressed");
    return 1;
  }
  else if (buttonValue > 2300 && buttonValue < 2500)
  {
    Serial.println("Button 2 pressed");
    return 2;
  }
  else if (buttonValue > 1500 && buttonValue < 1700)
  {
    Serial.println("Button 3 pressed");
    return 3;
  }
  else if (buttonValue < 1000)
  {
    return 0;
  }
  return 0;

  if (digitalRead(SAFETY_SWITCH) == HIGH) { // Plinth safety switch
    alarmState = 4;  // Cover removed error
  }
}
