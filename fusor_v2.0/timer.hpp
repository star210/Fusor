#pragma once

#include "util.hpp"

class _Timer {
  public:

      bool pressed (int delayTime) {
      auto now = millis();
      if (now - pressedStartTime > delayTime) {
        pressedStartTime = now;
        return true;
      }
      return false;
    }
    
    bool print (int delayTime) {
      auto now = millis();
      if (now - printStartTime > delayTime) {
        printStartTime = now;
        return true;
      }
      return false;
    }

        bool state (int delayTime) {
      auto now = millis();
      if (now - stateStartTime > delayTime) {
        if (!timerOn) {
          timerOn = true;
          stateStartTime = now;
          return false;
        }
        timerOn = false;
        return true;
      }
      return false;
    }

    bool pressure (int delayTime) {
      auto now = millis();
      if (now - pressureStartTime > delayTime) {
        pressureStartTime = now;
        return true;
      }
      return false;
    }

        bool variac (int delayTime) {
      auto now = millis();
      if (now - variacStartTime > delayTime) {
        variacStartTime = now;
        return true;
      }
      return false;
    }
    

bool timerOn = false;
uint32_t stateStartTime = 0;
uint32_t variacStartTime = 0;
uint32_t pressureStartTime = 0;
uint32_t printStartTime = 0;
uint32_t pressedStartTime = 0;
};
extern _Timer Timer;
