
#include "pins.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>

#define precision 12 // OneWire precision (9 - 12 bit range)

#define VACCUUM_PUMP_TEMP_MAX 140
#define PLASMA_PLATE_TEMP_MAX 100
#define TRANSFORMER_TEMP_MAX 90

int SensorNumber = 0; // Counter of sensors

unsigned long previousTempReadTime = 0;      

float vacuumPumpTemp = 0;
float plasmaPlateTemp = 0;
float transformerTemp = 0;

OneWire oneWire(TEMP_SENSOR);// Temp sensor pin
// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);
// Addresses of DS18B20 sensors connected to the 1-Wire bus
byte sensor1[8] = {0x28, 0xAA, 0x50, 0x77, 0x91, 0x0F, 0x02, 0x11};
byte sensor2[8] = {0x28, 0xCB, 0xE9, 0x1D, 0x07, 0x00, 0x00, 0x8F};
byte sensor3[8] = {0x28, 0xE7, 0x65, 0x77, 0x91, 0x10, 0x02, 0x8C};

void setup() {
  sensors.begin();
  Serial.print("Found: ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" Temp Sensors");
}

void update() {

  unsigned long tempReadTime = millis(); // timer to read temp every 1 second

  if (tempReadTime - previousTempReadTime >= 1000) { // Read and update only if 1 second has passed
    sensors.requestTemperatures();
    vacuumPumpTemp = getTemperature(sensor1);
    plasmaPlateTemp = getTemperature(sensor2);
    transformerTemp = getTemperature(sensor3);

    if (vacuumPumpTemp > VACCUUM_PUMP_TEMP_MAX) {
      alarmState = 1;
    }
    if (plasmaPlateTemp > PLASMA_PLATE_TEMP_MAX) {
      alarmState = 2;
    }
    if (transformerTemp > TRANSFORMER_TEMP_MAX) {
      alarmState = 3;
    }
    previousTempReadTime = tempReadTime;  
}

void printTemperature() {
  Serial.print("Vacuum Pump Temp: "); Serial.print(vacuumPumpTemp); Serial.print(" \xC2\xB0"); Serial.println("C");
  Serial.print("Plasma Plate Temp: "); Serial.print(plasmaPlateTemp); Serial.print(" \xC2\xB0"); Serial.println("C");
  Serial.print("Transformer Temp: "); Serial.print(transformerTemp); Serial.print(" \xC2\xB0"); Serial.println("C");
}

void getTemperature(DeviceAddress address) {
  // Fetch the temperature in degrees Celsius for device address:
  float tempC = sensors.getTempC(address);
  return tempC;
}
