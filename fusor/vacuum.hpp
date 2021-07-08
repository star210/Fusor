#pragma once

#include "pins.hpp"

#define PUMP_TIMEOUT  180;    //Seconds, Seal leak causing it to never get to vacuum
#define MIN_PRESSURE            //milliTorr pressure must 

// 1 atm = 1 torr/760
// interpolating lookup table "LUT" in PROGMEM 

bool pumpRelayState = 0; // 
 
void setup() {
 
  pinMode(VACUUM_PUMP_RELAY, OUTPUT);
  digitalWrite(VACUUM_PUMP_RELAY, LOW); 
}

void update() {
  digitalWrite(VACUUM_PUMP_RELAY, pumpRelayState);  // update pump relay state serial input used to turn on/off
}
