
/* To do
  - add wifi manager
  - add MQTT
  - redo setting char names
  - button debounce
  - wipe memory function missing
  - add sensor divider to settings
  SENSORS
  - Make and update to read sensors and trigger alarms?
  - Find correct vacuum unit uTorr?
  VARIAC
  - move variac to 0 on setup
  - tune PID or amps for smooth transition.
  OLED
  - Only display messages
  - Button press temps ?

*/




#define DEBUG
#define OLED  // Define to print to oled

#include <Wire.h>

#include "buttons.hpp"
#include "vacuum.hpp"
#include "alarm.hpp"
#include "temp.hpp"
#include "timer.hpp"
#include "variac.hpp"
#include "settings.hpp"
#include "oled.hpp"
#include "serial.hpp"

// define externs
_Settings Settings;
_Alarm Alarm;
_Sensors Sensors;
_Temp Temp;
_Variac Variac;
_Timer Timer;

_Oled Oled;
_Vacuum Vacuum;

Buttons buttons;
serial serial;

enum State {
  IDLE,
  VACUUM,
  VOLTAGE_UP,
  PLASMA,
  VOLTAGE_DOWN,
  COOLDOWN,
  ALARM
} state;

const char* currentStateName() {
  switch (state) {
    case IDLE: return "IDLE";
    case VACUUM: return "VACUUM";
    case VOLTAGE_UP: return "VOLTAGE_UP";
    case PLASMA: return "PLASMA";
    case VOLTAGE_DOWN: return "VOLTAGE_DOWN";
    case COOLDOWN: return "COOLDOWN";
    case ALARM: return "ALARM";
  }
  return "UNKOWN";
}

void transition(State nextState) {
  state = nextState;
  debugln("transitioning to state", currentStateName());
  Oled.displayln("State: ", currentStateName());
}

void setup() {
  Serial.begin(115200);
  delay(2000);
  Settings.begin();
  Sensors.begin();
  Variac.begin();
  Temp.begin();
  Wire.begin(16, 17, 100000);  // this should be after Sensors.begin()
  delay(100);
  Sensors.scanAddress();
  buttons.setup();
  Vacuum.begin();
  Oled.begin();
  debugln("Fusor version:", settings.softwareVersion);  // this should be after Settings.begin()
  delay(100);
  transition(IDLE);
}

void loop() {

  Temp.update();
  Vacuum.update();
  Variac.update();
  serial.update();

  if (isCoverRemoved()) {
    Alarm.raise(COVER_REMOVED);
  }

  if (buttons.pressed() == Buttons::DOWN) {
    transition(IDLE);
  }

  if (!Alarm.OK() && state != ALARM) {
    transition(ALARM);
  }

  if (Timer.print(settings.updateInterval)) {
    if (Temp.Print()) {
      debugln("Pump Temp:", Temp.getPump(), "Plate Temp:", Temp.getPlasma(), "Transformer Temp:", Temp.getTransformer());
    }
    if (Vacuum.Print()) {
      debug("Vaccuum Pressure: ", Sensors.getVacuumPressure(), "Torr");
      Serial.print(Sensors.getVacuumPressure() / 760, 8); 
      Serial.println(" Atmospheres");
    }
    if (Variac.Print()) {  
      Variac.printMotor(); 
      debugln("Variac Current: ", Sensors.getVariacCurrent(), " mA AC");
      debugln("Variac Voltage: ", Sensors.getVariacVoltage(), " V AC");
    }
  }

  switch (state) {
    case IDLE:
      {
        // auto pressed = buttons.pressed();
        if (buttons.pressed() == Buttons::SELECT) {
          transition(VACUUM);
        }
      }
      break;

    case VACUUM:
      {
        Vacuum.enable();
        if (Vacuum.isReady()) {
          debugln("vacuum is at", Vacuum.vacuumPressure);
          transition(VOLTAGE_UP);
        }
      }
      break;

    case VOLTAGE_UP:
      {
        Variac.enable();
        if (Variac.setVoltage (settings.plasmaVolts, settings.stepTime)) {
          debugln("Plasma voltage reached");
          transition(PLASMA);
        }
      }
      break;

    case PLASMA:
      {
        if (Timer.state(settings.plasmaTime)) {
          debugln("Plasma finished");
          transition(VOLTAGE_DOWN);
        }
      }
      break;

    case VOLTAGE_DOWN:
      {
        if (Variac.setVoltage (0, settings.stepTime)) {
          debugln("Voltage down finished");
          Variac.disable();
          transition(COOLDOWN);

        }
      }
      break;

    case COOLDOWN:
      {
        if (Timer.state(settings.coolDownTime)) {
          debugln("Cooldown finished");
         // transition(VACUUM);         // Undefine to cycle back to vacuum
          transition(IDLE);             // Undefine to end cycle and go to idle
          
        }
      }
      break;

    case ALARM:
      {
        Vacuum.disable();
        Variac.disable();
        if (buttons.pressed() == Buttons::UP) {
          Alarm.clear();
          transition(IDLE);
        }
      }
      break;
  }
}
