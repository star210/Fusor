#pragma once

#include "pins.hpp"

#define PUMP_TIMEOUT  180;    //Seconds, Seal leak causing it to never get to vacuum
#define MIN_PRESSURE            //milliTorr lower pressure limit
#define MAX_PRESSUE            // milliTorr upper pressure limit

// 1 atm = 1 torr/760
// interpolating lookup table "LUT" in PROGMEM

bool pumpRelayState = 0;
bool pumpStarted = 0;
bool vacuumPump = 0;  pump routine off

void setup() {

  pinMode(VACUUM_PUMP_RELAY, OUTPUT);
  digitalWrite(VACUUM_PUMP_RELAY, LOW);
}

void update() {

  if (vacuumPump) {
    if (vacuumPressure < MIN_PRESSURE) {        // if vacuum is not at a suitable level for high voltage to start
      if (!pumpStarted) {  // if pump hasnt started yet
        Serial.println("Below min pressure, vacuum pump started");
        unsigned long pumpStarted = timeNow;
        pumpRelayState = 1;         //Start pump
        pumpStarted = 1;
      }
      if (timenow > pumpStarted + PUMP_TIMEOUT) {       // if pump has been on longer than timeout
        alarmState = 5;                 // Pump has been not achived vacuum within timeout period error
      }
    }
    else if (vacuumPressure > MAX_PRESSURE) {
      if (pumpStarted) {
        Serial.println("Above max pressure, vacuum pump stopped");
        pumpRelayState = 0;         //Stop pump
        pumpStarted = 0;            // reset pump bool
      }
    }
  }
  digitalWrite(VACUUM_PUMP_RELAY, pumpRelayState);  // update pump relay state
}
