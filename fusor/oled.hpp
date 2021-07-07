#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pins.hpp"
#include "adc.hpp"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Wire.begin(16, 17);                            // Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(15, 15);
  display.println("NORVI IIOT-AE04-V");
  display.setCursor(45, 30);
  display.println("HELLO...");
  display.setCursor(25, 45);
  display.println("Test code V1.0");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.display();
  Serial.println("OLED setup complete");
}

void update() {


// High Voltage Relay State
  display.setCursor(75, 25);
  display.println("NST");
  display.setCursor(78, 35);
  display.println(digitalRead(26));
  
// Vacuum Pump Relay State
  display.setCursor(90, 25);
  display.println("PUMP");
  display.setCursor(93, 35);
  display.println(digitalRead(27));

// Safety Switch State
  display.setCursor(105, 25);
  display.println("SAFE");
  display.setCursor(108, 35);
  display.println(digitalRead(27));

  // Pressure
  display.setCursor(0, 5);
  display.println(vacuumPressure);
  display.setCursor(20, 5);
  display.println("mTorr");
  //Variac V
  display.setCursor(0, 15);
  display.println(variacVolts);
  display.setCursor(20, 15);
  display.println("V AC");
  //Variac mA
  display.setCursor(0, 25);
  display.println(variacAmps);
  display.setCursor(20, 25);
  display.println("mA AC");

  //NST KV
  display.setCursor(0, 35);
  display.println(highVoltageKiloVolts);
  display.setCursor(20, 35);
  display.println("KV DC");
  //NST mA
  display.setCursor(0, 45);
  display.println(highVoltageMilliAmps);
  display.setCursor(20, 45);
  display.println("mA DC");

  display.display();
  display.clearDisplay();
}
