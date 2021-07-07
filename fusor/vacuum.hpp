#pragma once

#include "pins.hpp"

// 1 atm = 1 torr/760
// interpolating lookup table "LUT" in PROGMEM 

bool pumpRelayState = 0; // 
 
void setup() {
 
  pinMode(VACUUM_PUMP_RELAY, OUTPUT);
  digitalWrite(VACUUM_PUMP_RELAY, LOW); 
}

void update() {
  digitalWrite(VACUUM_PUMP_RELAY, pumpRelayState);  // update pump relay state
}
