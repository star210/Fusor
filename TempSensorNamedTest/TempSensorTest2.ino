/* Read multiple DS18B20 1-Wire digital temperature sensors by address. More info: https://www.makerguides.com */
// Include the required Arduino libraries:
#include <OneWire.h>
#include <DallasTemperature.h>
// Define to which pin of the Arduino the 1-Wire bus is connected:
#define ONE_WIRE_BUS 16
// Create a new instance of the oneWire class to communicate with any OneWire device:
OneWire oneWire(ONE_WIRE_BUS);
// Pass the oneWire reference to DallasTemperature library:
DallasTemperature sensors(&oneWire);
// Addresses of DS18B20 sensors connected to the 1-Wire bus
byte sensor1[8] = {0x28, 0xAA, 0x50, 0x77, 0x91, 0x0F, 0x02, 0x11};
byte sensor2[8] = {0x28, 0xCB, 0xE9, 0x1D, 0x07, 0x00, 0x00, 0x8F};
byte sensor3[8] = {0x28, 0xE7, 0x65, 0x77, 0x91, 0x10, 0x02, 0x8C};
void setup() {
  // Begin serial communication at a baud rate of 9600:
  Serial.begin(9600);
  // Start up the library:
  sensors.begin();
}
void loop() {
  // Send the command for all devices on the bus to perform a temperature conversion:
  sensors.requestTemperatures();
  Serial.print("Vacuum Pump Temp: ");
  printTemperature(sensor1); // call the printTemperature function with the address of sensor1 as input
  Serial.print("Plasma Plate Temp: ");
  printTemperature(sensor2);
  Serial.print("Transformer Temp: ");
  printTemperature(sensor3);
  Serial.println(); // prints an empty line
  delay(1000);
}
void printTemperature(DeviceAddress address) {
  // Fetch the temperature in degrees Celsius for device address:
  float tempC = sensors.getTempC(address);
  // Fetch the temperature in degrees Fahrenheit for device address:
  float tempF = sensors.getTempF(address);
  Serial.print(tempC);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.print("C  |  ");
  // Print the temperature in Fahrenheit
  Serial.print(tempF);
  Serial.print(" \xC2\xB0"); // shows degree symbol
  Serial.println("F");
}
