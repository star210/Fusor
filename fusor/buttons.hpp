#pragma once

#include "pins.hpp"

int buttonType = 0;

void setup() {

  pinMode(BUTTON_PIN, INPUT);
  pinMode(FC, OUTPUT);
  digitalWrite(FC, HIGH); // FC needed for A0 to work???
  Serial.println("Buttons setup complete");
}

void loop() {

  buttonType = readButtons(BUTTON_PIN);
  Serial.println(buttonType);

}

int readButtons(int buttonPin) {
  int buttonValue  = 0;
  buttonValue = analogRead(buttonPin);     // read the value from the sensor
  delay(50);
  if (buttonValue > 3300 && buttonValue < 3600) {
    return 1;
  }
  else if (buttonValue > 2300 && buttonValue < 2500)
  {
    return 2;
  }
  else if (buttonValue > 1500 && buttonValue < 1700)
  {
    return 3;
  }
  else if (buttonValue < 1000)
  {
    return 0;
  }
  return 0;
}
