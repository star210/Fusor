#include "Arduino.h"

#include "pins.hpp"
#include "settings.hpp"
#include "util.hpp"
#include "vacuum.hpp"
#include "temp.hpp"

class serial {
  public:

    void update() {
      char cmd = Serial.read();
      // if (cmd > 'Z') cmd -= 32;
      switch (cmd) {
        case 'H': help(); break;
        case 'X': ESP.restart(); break;
        case 'S': Settings.printSettings(); break;
        case 'D': Settings.loadDefaultSettings(); break;
        case 'E': Settings.eraseMemory(); break;
        case 'W': Settings.saveToMemory(); break;
        case 'R': Settings.loadFromMemory(); break;
        case 'A': Alarm.clear(); break;
       // case 'B': Buttons.Start(); break;
        case 'T': Temp.Toggle(); break;
        case 'V': Vacuum.Toggle(); break;
        case 'C': Variac.Toggle(); break;


        case 'p': settings.motorP = Serial.parseFloat(); Variac.setPID(); break;
        case 'i': settings.motorI = Serial.parseFloat(); Variac.setPID(); break;
        case 'd': settings.motorD = Serial.parseFloat(); Variac.setPID(); break;
        case 'm': settings.plasmaTime = Serial.parseInt(); break;
        case 'c': settings.coolDownTime = Serial.parseInt(); break;
        case 'v': settings.plasmaVolts = Serial.parseInt(); break;
        case 's': settings.stepTime = Serial.parseInt(); break;
        case 'l': settings.maxVariacVoltage = Serial.parseInt(); break;
        case 'r': settings.maxVariacCurrent = Serial.parseInt(); break;
        case 'e': settings.maxMotorError = Serial.parseInt(); break;
        case 'o': settings.vacuumPumpTimeout = Serial.parseInt(); break;
        case 'n': settings.minVacuumPressure = Serial.parseFloat(); break;
        case 'x': settings.maxVacuumPressure = Serial.parseFloat(); break;
        case 'y': settings.updateInterval = Serial.parseInt(); break;
        case 'u': settings.maxPumpTemp = Serial.parseInt(); break;
        case 'a': settings.maxPlasmaTemp = Serial.parseInt(); break;
        case 't': settings.maxTransformerTemp = Serial.parseInt(); break;
      }
      //   while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
    }

    void help () {
      debugln("H - Print Help Menu");
      debugln("S - Print Settings Menu");
      debugln("X - Restart");
      debugln("D - Force Save Default Settings");
      debugln("E - Erase NVS memory");
      debugln("A - Clear Alarm");
      debugln("T - Toggle Temp Sensor Print");
      debugln("V - Toggle Vacuum Sensor Print");
      debugln("C - Toggle Variac PID variables");
      debugln("W - Save Settings To Memory");
      debugln("R - Load Settings From Memory");

      debugln("p - Set PID P Value");
      debugln("i - Set PID I Value");
      debugln("d - Set PID D Value");
      debugln("m - Set Plasma Time");
      debugln("c - Set Cooldown Time");
      debugln("v - Set Plasma Voltage");
      debugln("s - Set Step Time");
      debugln("l - Set Maximum Variac Voltage");
      debugln("r - Set Minimum Variac Voltage");
      debugln("e - Set Max Motor Error");
      debugln("o - Set Vacuum Pump Timeout");
      debugln("n - Set Minimum Vacuum Pressure");
      debugln("x - Set Maximum Vacuum Pressure");
      debugln("y - Set Update Interval");
      debugln("u - Set Max Pump Temp");
      debugln("a - Set Max Plasma Temp");
      debugln("t - Set Max Transformer Temp");
    }

};
