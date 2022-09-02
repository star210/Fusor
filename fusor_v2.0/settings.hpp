#pragma once

#include <Preferences.h>
#include "util.hpp"
#include "oled.hpp"

//enum settingsVocab {
//  SOFTWARE_VERSION,
//  PLASMA_TIME,
//  COOLDOWN_TIME,
//  PLASMA_VOLTAGE,
//  STEP_TIME,
//  MAX_VARIAC_VOLTAGE,
//  MAX_VARIAC_CURRENT,
//  MAX_MOTOR_ERROR,
//  MOTOR_P,
//  MOTOR_I,
//  MOTOR_D,
//  VACUUM_PUMP_TIMEOUT,
//  MIN_VACUUM_PRESSURE,
//  MAX_VACUUM_PRESSURE,
//  UPDATE_INTERVAL,
//  MAX_PUMP_TEMP,
//  MAX_PLASMA_TEMP,
//  MAX_TRANSFORMER_TEMP,
//};
//
//char* memoryName(int settingsVocab) {
//  switch (settingsVocab) {
//    case SOFTWARE_VERSION: return "softVer";
//    case PLASMA_TIME: return "plasmaTime";
//    case COOLDOWN_TIME: return "coolTime";
//    case PLASMA_VOLTAGE: return "plasmaVolts";
//    case STEP_TIME: return "stepTime";
//    case MAX_VARIAC_VOLTAGE: return "maxVarVolts";
//    case MAX_VARIAC_CURRENT: return "maxVarCurr";
//    case MAX_MOTOR_ERROR: return "maxMotorErr";
//    case MOTOR_P: return "motorP";
//    case MOTOR_I: return "motorI";
//    case MOTOR_D: return "motorD";
//    case VACUUM_PUMP_TIMEOUT: return "vacPumpTout";
//    case MIN_VACUUM_PRESSURE: return "minVacPress";
//    case MAX_VACUUM_PRESSURE: return "maxVacPres";
//    case UPDATE_INTERVAL: return "updateInt";
//    case MAX_PUMP_TEMP: return "maxPumpTemp";
//    case MAX_PLASMA_TEMP: return "maxPlasmaTemp";
//    case MAX_TRANSFORMER_TEMP: return "maxTransTemp";
//  }
//  return "UNKNOWN";
//}

#define DATA_SIZE 18
struct __attribute((__packed__)) settings_t {
  float softwareVersion;
  uint16_t plasmaTime;
  uint16_t coolDownTime;
  uint16_t plasmaVolts;
  uint16_t stepTime;
  uint16_t maxVariacVoltage;
  uint16_t maxVariacCurrent;
  uint16_t maxMotorError;
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

settings_t settings;
//
//typedef union loop_t {
//  settings structure;
//  int value[DATA_SIZE]; /* you can use other variable types if you want. Like: a 32bit integer if you have 4 8bit variables in your struct */
//};
//loop_t settings;

class _Settings {
  public:

    void begin() {
      loadFromMemory();           // Recover settings from NVS memory
      if (settings.softwareVersion == 0) {
        debugln("Default settings not loaded");
        //loadDefaultSettings();    // Load defaults to NVS memory
      }
      printSettings();
    }

    void printSettings () {
      //      for (int i = 0; i < DATA_SIZE; i++) {
      //        debugln(memoryName(i), settings.value[i]);
      //      }
      debugln(sizeof(settings_t), "bytes of settings");
      debugln("Software Version:", settings.softwareVersion);
      debugln("Plasma Time:", settings.plasmaTime);
      debugln("Cooldown Time:", settings.coolDownTime);
      debugln("Plasma Volts:", settings.plasmaVolts);
      debugln("Steptime:", settings.stepTime);
      debugln("Max Variac Voltage:", settings.maxVariacVoltage);
      debugln("Max Variac Current:", settings.maxVariacCurrent);
      debugln("Max Motor Error:", settings.maxMotorError);
      debugln("Motor P:", settings.motorP);
      debugln("Motor I", settings.motorI);
      debugln("Motor D:", settings.motorD);
      debugln("Vacuum Timeout:", settings.vacuumPumpTimeout);
      debugln("Min Vacuum Pressure:", settings.minVacuumPressure);         // Measured in Torr
      debugln("Max Vacuum Pressure:", settings.maxVacuumPressure);         // Measured in Torr
      debugln("Update Interval:", settings.updateInterval);
      debugln("Max Pump Temp:", settings.maxPumpTemp);
      debugln("Max Plasma Temp:", settings.maxPlasmaTemp);
      debugln("Max Transformer Temp:", settings.maxTransformerTemp);

    }

    void saveToMemory () {
      preferences.begin("settings", false);
      preferences.putBytes("settings", &settings, sizeof(settings_t));
      preferences.end();
      debugln(sizeof(settings_t), "bytes of settings loaded to NVS memory");
      Oled.displayln("Saved to memory");
    }

    void eraseMemory () {
      preferences.begin("settings", false);
      preferences.clear();
      preferences.end();
      debugln("NVS memory erased");
    }

    void loadFromMemory () {
      preferences.begin("settings", false);
      preferences.getBytes("settings", &settings, sizeof(settings_t));
      preferences.end();
      debugln("settings loaded from NVS memory");
      Oled.displayln("Loaded from memory");
    }

    void loadDefaultSettings () {
      settings.softwareVersion = 1.8;
      settings.plasmaTime = 3000;
      settings.coolDownTime = 3000;
      settings.plasmaVolts = 200;
      settings.stepTime = 200;
      settings.maxVariacVoltage = 230;
      settings.maxVariacCurrent = 2000;
      settings.maxMotorError = 50;
      settings.motorP = 10.0;
      settings.motorI = 20.0;
      settings.motorD = 0.0;
      settings.vacuumPumpTimeout = 10000;
      settings.minVacuumPressure = 0.2;         // Measured in Torr
      settings.maxVacuumPressure = 0.02;         // Measured in Torr
      settings.updateInterval = 10000;
      settings.maxPumpTemp = 140;
      settings.maxPlasmaTemp = 100;
      settings.maxTransformerTemp = 100;

      debugln("Default settings loaded");
    }

  public:
    Preferences preferences;
};

extern _Settings Settings;
