#pragma once

#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1(0x48);      // 0 - 10v input
Adafruit_ADS1115 ads2(0x49);      // 0 - 5v input

float VacuumPressure = 0.0;          // ads1 CH0 - A0 Norvi 0 - 10v
float VariacVolts = 0.0;             // ads1 CH1 - A1 Norvi 0 - 10v
float VariacAmps = 0.0;              // ads1 CH2 - A2 Norvi 0 - 10v
float HighVoltageKiloVolts = 0.0;    // ads2 CH0 - A4 Norvi 0 - 5v
float HighVoltageMilliAmps = 0.0;    // ads2 CH1 - A5 Norvi 0 - 5v

void setup() {
  ads1.begin();
  ads2.begin();

  //ads1.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)
  ads1.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV
  ads2.setGain(GAIN_ONE);     // 1x gain   +/- 4.096V  1 bit = 2mV
  Serial.println("ADC setup complete");
}

void update()
{
  float adc0;
  float adc1;
  float adc2;
  float adc3;
  float adc4;

  adc0 = ads1.readADC_SingleEnded(0);
  adc1 = ads1.readADC_SingleEnded(1);
  adc2 = ads1.readADC_SingleEnded(2);
  adc3 = ads2.readADC_SingleEnded(0);
  adc4 = ads2.readADC_SingleEnded(1);

  VacuumPressure = (adc0 * 0.1875) / 1000;
  VariacVolts = (adc1 * 0.1875) / 1000;
  VariacAmps = (adc2 * 0.1875) / 1000;
  HighVoltageKiloVolts = (adc3 * 0.1875) / 1000;
  HighVoltageMilliAmps = (adc4 * 0.1875) / 1000;
