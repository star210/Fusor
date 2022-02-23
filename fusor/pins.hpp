#pragma once

enum Pins {
  FC = 4,                   // Needs to be high for GPIO32 to work!
  VACUUM_PUMP_RELAY = 26,   // T0 vacuum pump relay
  VARIAC_RELAY = 27,        // T1 high voltage relay
  SAFETY_SWITCH = 34,       // Plinth safety microswitch
  BUTTONS = 32,             // Analog input
  TEMP_SENSOR = 0,          // DS18B20 sensor data line GPIO 0 IDC pin 5
};
