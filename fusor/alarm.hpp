#pragma once

enum AlarmBit {
  VACUUM_PUMP_OVERHEAT = 1,
  PLASMA_PLATE_OVERHEAT = 2,
  TRANSFORMER_OVERHEAT = 4,
  COVER_REMOVED = 8,
  VACUUM_LEAK_DETECTED = 16,
  VARIAC_MOTOR_ERROR = 32,
  VARIAC_OVERCURRENT = 64,
};

const char* alarmBitName(AlarmBit bit) {
  switch (bit) {
    case VACUUM_PUMP_OVERHEAT: return "VACUUM_PUMP_OVERHEAT";
    case PLASMA_PLATE_OVERHEAT: return "PLASMA_PLATE_OVERHEAT";
    case TRANSFORMER_OVERHEAT: return "TRANSFORMER_OVERHEAT";
    case COVER_REMOVED: return "COVER_REMOVED";
    case VACUUM_LEAK_DETECTED: return "VACUUM_LEAK_DETECTED";
    case VARIAC_MOTOR_ERROR: return "VARIAC_MOTOR_ERROR";
    case VARIAC_OVERCURRENT: return "VARIAC_OVERCURRENT";
  }
  return "UNKNOWN";
}

class _Alarm {
  public:
    void raise(AlarmBit bit) {
      if ((currentState & bit) == 0) {
        currentState |= bit;
        debugln("alarm raised on", alarmBitName(bit));
        Oled.displayln(alarmBitName(bit));
      }
    }

    bool OK() {
      return currentState == 0;
    }

    void clear() {
      currentState = 0;
    }
    int currentState = 0;
};

extern _Alarm Alarm;
