#pragma once

#include <Arduino.h>
#include "pins.hpp"
#include "sensors.hpp"
#include "util.hpp"
#include "alarm.hpp"
#include "settings.hpp"
#include "timer.hpp"

class _Vacuum {
  public:
    void begin() {
      pinMode(VACUUM_PUMP_RELAY, OUTPUT);
      digitalWrite(VACUUM_PUMP_RELAY, LOW);
    }

    void enable(bool on = true) {
      enabled = on;
    }

    void disable() {
      enabled = false;
    }

    void update() {
      if (enabled) {
        auto timeNow = millis();
        if (Timer.pressure(200)){  // Update vacuum pressure
        vacuumPressure = Sensors.getVacuumPressure();
       // debugln("Vaccuum Pressure: ", vacuumPressure, "Torr");
        }
        if (vacuumPressure > settings.structure.minVacuumPressure) {        // if vacuum is not at a suitable level for high voltage to start
          if (!pumpRelayState) {  // if pump hasnt started yet
            debugln("Below min pressure, vacuum pump started");
            pumpRelayState = 1;
            pumpStartTime = timeNow;
          } 
          else if (timeNow > pumpStartTime + settings.structure.vacuumPumpTimeout) {       // if pump has been on longer than timeout
           // Alarm.raise(VACUUM_LEAK_DETECTED); // Pump has been not achived vacuum within timeout period error
           // pumpRelayState = 0;
          }
        }
        else if (vacuumPressure < settings.structure.maxVacuumPressure) {
          if (pumpRelayState) {
            debugln("Above max pressure, vacuum pump stopped");
            pumpRelayState = 0;
          }
        }
      }
      else {
        pumpRelayState = 0;
      }
      digitalWrite(VACUUM_PUMP_RELAY, pumpRelayState);  // update pump relay state
    }

    bool isReady() {
      return vacuumPressure < settings.structure.minVacuumPressure;
    }

    void turnRelayOn(bool on = true) {
      pumpRelayState = on;
    }

    bool Print() {
      return printVacuum;
    }

    void Toggle() {
      printVacuum = ! printVacuum;
    }

  public:
    bool enabled = false;
    bool printVacuum = false;
    bool pumpRelayState = false;
    uint32_t pumpStartTime = 0;
    double vacuumPressure = 1000;
};

extern _Vacuum Vacuum;
