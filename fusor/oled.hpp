#pragma once

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "pins.hpp"

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
