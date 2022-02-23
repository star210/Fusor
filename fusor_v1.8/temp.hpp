#pragma once

#include <OneWire.h>
#include <DallasTemperature.h>

#include "settings.hpp"
#include "pins.hpp"
#include "util.hpp"

byte vacuumSensor[8] = {0x28, 0xAA, 0x50, 0x77, 0x91, 0x0F, 0x02, 0x11};
byte plasmaSensor[8] = {0x28, 0xCB, 0xE9, 0x1D, 0x07, 0x00, 0x00, 0x8F};
byte transormerSensor[8] = {0x28, 0xE7, 0x65, 0x77, 0x91, 0x10, 0x02, 0x8C};

class _Temp {
  public:
    _Temp(): oneWire(Pins::TEMP_SENSOR), sensors(&oneWire) {}

    void begin() {
      sensors.begin();
      debugln("found", sensors.getDeviceCount(), "sensors");
      debugln("Temp setup complete");
    }

    void update() {
      auto timeNow = millis();
      if (timeNow > lastUpdateTime + settings.structure.updateInterval) {
        lastUpdateTime = timeNow;
        sensors.requestTemperatures();
        pumpTemp = sensors.getTempC(vacuumSensor);
        plateTemp = sensors.getTempC(plasmaSensor);
        transformerTemp = sensors.getTempC(transormerSensor);
      }
      if (pumpTemp > settings.structure.maxPumpTemp) {
        Alarm.raise(VACUUM_PUMP_OVERHEAT);
      }
      if (plateTemp > settings.structure.maxPlasmaTemp) {
        Alarm.raise(PLASMA_PLATE_OVERHEAT);
      }
      if (transformerTemp > settings.structure.maxTransformerTemp) {
        Alarm.raise(TRANSFORMER_OVERHEAT);
      }
    }

    double getPump() {
      return pumpTemp;
    }
    double getPlasma() {
      return plateTemp;
    }
    double getTransformer() {
      return transformerTemp;
    }

    bool Print() {
      return printTemp;
    }

    void Toggle() {
      printTemp = ! printTemp;
    }

  public:
    uint32_t lastUpdateTime = 0;
    OneWire oneWire;
    DallasTemperature sensors;
    bool printTemp = false;
    float pumpTemp, plateTemp, transformerTemp;
};

extern _Temp Temp;
