#pragma once

// 3.3k - 2.2k resistor divider 10v in 4v out - adc volts x 2.5
// ads1115 15bit resolution ADS1115 - 32768
//
// Volts Variac multiplier 0 - 300v
// 32768 / 8000 = 4.096v 32000 / 8000 = 4v
// 4v * 2.5 = 10v
// 10v * 30 = 300v
// 32000 / 106.66666 = 300v
//
// Amps Variac multiplier 0 - 2000mA
// 32768 / 8000 = 4.096v 32000 / 8000 = 4v
// 4v * 2.5 = 10v
// 10v * 200 = 2000mA
// 32000 / 16 = 2000mA
//
// High Voltage 0 - 10000v
// 32768 / 16000 = 2.048v 32000 / 16000 = 2v
// 2v * 2.5 = 5v
// 5v * 2000 = 10000v
// 32000 / 3.2 = 10000v
//
// High Voltage 0 - 50mA
// 32768 / 16000 = 2.048v 32000 / 16000 = 2v
// 2v * 2.5 = 5v
// 5v * 10 = 50mA
// 32000 / 640 = 50mA

#include <Adafruit_ADS1015.h>

Adafruit_ADS1115 ads1(0x48);      // 0 - 10v input
Adafruit_ADS1115 ads2(0x49);      // 0 - 5v input

//ads1 gain x1
float vacuumPressure = 0.0;          // ads1 CH0 - A0 Norvi 0 - 10v 0.8 - 3.2v
float variacVolts = 0.0;             // ads1 CH1 - A1 Norvi 0 - 10v 0 - 4v
float variacMilliAmps = 0.0;              // ads1 CH2 - A2 Norvi 0 - 10v 0 - 4v
//ads2 gain x2
float highVoltageKiloVolts = 0.0;    // ads2 CH0 - A4 Norvi 0 - 5v 0 - 2v
float highVoltageMilliAmps = 0.0;    // ads2 CH1 - A5 Norvi 0 - 5v 0 - 2v

unsigned long currentTime = millis();
unsigned long previousTime = 0;

bool sensorSerialPrint = 0;  //

void setup() {
  ads1.begin();
  ads2.begin();

  //ads1.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)
  ads1.setGain(GAIN_ONE);     // 1x gain   +/- 4.096V  1 bit = 2mV
  ads2.setGain(GAIN_TWO);     // 2x gain for an input range of +/-2.048V)
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

  vacuumPressure = adc0;  // LUT needed
  variacVolts = adc1 / 106.6666;
  variacMilliAmps = adc2 / 16;
  highVoltageKiloVolts = adc3 / 3.2;
  highVoltageMilliAmps = adc4 / 640;
}

void printSensorValues() {
      Serial.print("Vacuum Pressure: "); Serial.print(vacuumPressure); Serial.println(" mTorr");
      Serial.print("Variac Voltage: "); Serial.print(variacVolts); Serial.println(" Volts AC");
      Serial.print("Variac Current: "); Serial.print(variacMilliAmps); Serial.println(" mA AC");
      Serial.print("NST Voltage: "); Serial.print(highVoltageKiloVolts); Serial.println(" KV DC");
      Serial.print("NST Current: "); Serial.print(highVoltageMilliAmps); Serial.println(" mA DC");
    }
