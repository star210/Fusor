#pragma once

#include "Arduino.h"

enum Pins {
  FC = 2,                   // RS485 flow control (Needs to be high for GPIO32 to work!
  VACUUM_PUMP_RELAY = 26;   // T0 vacuum pump relay
  HIGH_VOLTAGE_RELAY = 27;  // T1 high voltage relay
  SAFETY_SWITCH = 34;       // Plinth safety microswitch
  BUTTONS = 32,             // Analog input
  TEMP_SENSOR = 25;         // DS18B20 sensor data line 
  M1 = 17;                  // DC motor driver IN1
  M2 = 16;                   // DC motor driver IN2
};
