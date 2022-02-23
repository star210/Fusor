#pragma once

#include <Preferences.h>
#include "util.hpp"
#include "oled.hpp"

enum settingsVocab {
  SOFTWARE_VERSION,
  PLASMA_TIME,
  COOLDOWN_TIME,
  PLASMA_VOLTAGE,
  STEP_TIME,
  MAX_VARIAC_VOLTAGE,
  MAX_VARIAC_CURRENT,
  MAX_MOTOR_ERROR,
  MOTOR_P,
  MOTOR_I,
  MOTOR_D,
  VACUUM_PUMP_TIMEOUT,
  MIN_VACUUM_PRESSURE,
  MAX_VACUUM_PRESSURE,
  UPDATE_INTERVAL,
  MAX_PUMP_TEMP,
  MAX_PLASMA_TEMP,
  MAX_TRANSFORMER_TEMP,
};

char* memoryName(int settingsVocab) {
  switch (settingsVocab) {
    case SOFTWARE_VERSION: return "softVer";
    case PLASMA_TIME: return "plasmaTime";
    case COOLDOWN_TIME: return "coolTime";
    case PLASMA_VOLTAGE: return "plasmaVolts";
    case STEP_TIME: return "stepTime";
    case MAX_VARIAC_VOLTAGE: return "maxVarVolts";
    case MAX_VARIAC_CURRENT: return "maxVarCurr";
    case MAX_MOTOR_ERROR: return "maxMotorErr";
    case MOTOR_P: return "motorP";
    case MOTOR_I: return "motorI";
    case MOTOR_D: return "motorD";
    case VACUUM_PUMP_TIMEOUT: return "vacPumpTout";
    case MIN_VACUUM_PRESSURE: return "minVacPress";
    case MAX_VACUUM_PRESSURE: return "maxVacPres";
    case UPDATE_INTERVAL: return "updateInt";
    case MAX_PUMP_TEMP: return "maxPumpTemp";
    case MAX_PLASMA_TEMP: return "maxPlasmaTemp";
    case MAX_TRANSFORMER_TEMP: return "maxTransTemp";
  }
  return "UNKNOWN";
}

#define DATA_SIZE 18
struct __attribute((__packed__)) settings_t {
  float softwareVersion;
  uint16_t plasmaTime;
  uint16_t coolDownTime;
  uint16_t plasmaVolts;
  uint16_t stepTime;
  uint16_t maxVariacVoltage;
  uint16_t maxVariacCurrent;
  uint8_t maxMotorError;
  float motorP;
  float motorI;
  float motorD;
  uint32_t vacuumPumpTimeout;
  float minVacuumPressure;
  float maxVacuumPressure;
  uint16_t updateInterval;
  uint8_t maxPumpTemp;
  uint8_t maxPlasmaTemp;
  uint8_t maxTransformerTemp;
};


typedef union loop_t {
  settings_t structure;
  int value[DATA_SIZE]; /* you can use other variable types if you want. Like: a 32bit integer if you have 4 8bit variables in your struct */
};
loop_t settings;

class _Settings {
  public:

    void begin() {
      //loadDefaultSettings();    // Load defaults to NVS memory
      loadFromMemory();           // Recover settings from NVS memory
      printSettings();
    }

    void printSettings () {
      for (int i = 0; i < DATA_SIZE; i++) {
        debugln(memoryName(i), settings.value[i]);
      }
    }

    void saveToMemory () {
      preferences.begin("settings", false);
      preferences.putBytes("settings", &settings, sizeof(settings_t));
      preferences.end();
      debugln("settings loaded to NVS memory");
      Oled.displayln("Saved to memory");
    }

    void loadFromMemory () {
      preferences.begin("settings", false);
      preferences.getBytes("settings", &settings, sizeof(settings_t));
      preferences.end();
      debugln("settings loaded from NVS memory");
      Oled.displayln("Loaded from memory");
    }

    void loadDefaultSettings () {
      settings.structure.softwareVersion = 1.8;
      settings.structure.plasmaTime = 3000;
      settings.structure.coolDownTime = 3000;
      settings.structure.plasmaVolts = 200;
      settings.structure.stepTime = 200;
      settings.structure.maxVariacVoltage = 230;
      settings.structure.maxVariacCurrent = 2000;
      settings.structure.maxMotorError = 50;
      settings.structure.motorP = 10.0;
      settings.structure.motorI = 20.0;
      settings.structure.motorD = 0.0;
      settings.structure.vacuumPumpTimeout = 10000;
      settings.structure.minVacuumPressure = 0.2;         // Measured in Torr
      settings.structure.maxVacuumPressure = 0.02;         // Measured in Torr
      settings.structure.updateInterval = 10000;
      settings.structure.maxPumpTemp = 140;
      settings.structure.maxPlasmaTemp = 100;
      settings.structure.maxTransformerTemp = 100;
      saveToMemory();
    }

  public:
    Preferences preferences;
};

extern _Settings Settings;
