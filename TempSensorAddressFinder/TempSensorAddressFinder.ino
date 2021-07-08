#include <OneWire.h>
#include <DallasTemperature.h>

#define ADDR_LEN 8
#define PIN 32

OneWire oneWire(PIN);
DallasTemperature sensors(&oneWire);

////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600L);
  Serial.println("ds18xx-list-devices started");
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
  Serial.println("----------------------------------------------------");

sensors.begin();

int deviceCount = sensors.getDeviceCount();
  Serial.print("Devices: ");
  Serial.println(deviceCount);

int ds18Count = sensors.getDS18Count();
  Serial.print("DS18xx devices: ");
  Serial.println(ds18Count);

uint8_t address[ADDR_LEN];
  for (int i = 0; i < deviceCount; ++i) {
    if (sensors.getAddress(address, i)) {
      Serial.print("Address: ");
      printAddress(address);
    }
  }
  delay(5000);
}

////////////////////////////////////////////////////////////////////////////////////////////////////
void printAddress(const uint8_t *address) {
  for (int i = 0; i < ADDR_LEN; ++i) {
    Serial.print("0x");
    if (address[i] < 0x10) {
      Serial.print("0");
    }
    Serial.print(address[i], HEX);
    if (i < 7) {
      Serial.print(", ");
    }
  }
  if (!sensors.validFamily(address)) {
    Serial.print(" (not supported)");
  }
  Serial.println();
}
