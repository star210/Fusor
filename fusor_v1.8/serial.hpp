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
        case 'S': Settings.printSettings();
        case 'A': Alarm.clear(); break;
        case 'B': Start(); break;
        case 'T': Temp.Toggle(); break;
        case 'V': Vacuum.Toggle(); break;
        case 'C': Variac.Toggle(); break;
        case 'W': Settings.saveToMemory(); break;
        case 'R': Settings.loadFromMemory(); break;
        
        case 'p': settings.structure.motorP = Serial.parseFloat(); Variac.setPID(); break;
        case 'i': settings.structure.motorI = Serial.parseFloat(); Variac.setPID(); break;
        case 'd': settings.structure.motorD = Serial.parseFloat(); Variac.setPID(); break;
        case 'm': settings.structure.plasmaTime = Serial.parseInt(); break;
        case 'c': settings.structure.coolDownTime = Serial.parseInt(); break;
        case 'v': settings.structure.plasmaVolts = Serial.parseInt(); break;
        case 's': settings.structure.stepTime = Serial.parseInt(); break;
        case 'l': settings.structure.maxVariacVoltage = Serial.parseInt(); break;
        case 'r': settings.structure.maxVariacCurrent = Serial.parseInt(); break;
        case 'e': settings.structure.maxMotorError = Serial.parseInt(); break;
        case 'o': settings.structure.vacuumPumpTimeout = Serial.parseInt(); break;
        case 'n': settings.structure.minVacuumPressure = Serial.parseFloat(); break;
        case 'x': settings.structure.maxVacuumPressure = Serial.parseFloat(); break;
        case 'y': settings.structure.updateInterval = Serial.parseInt(); break;
        case 'u': settings.structure.maxPumpTemp = Serial.parseInt(); break;
        case 'a': settings.structure.maxPlasmaTemp = Serial.parseInt(); break;
        case 't': settings.structure.maxTransformerTemp = Serial.parseInt(); break;
      }
   //   while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
    }

    void help () {
      debugln("H - Print Help Menu");
      debugln("S - Print Settings Menu");
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
      debugln("i - Set Update Interval");
      debugln("u - Set Max Pump Temp");
      debugln("a - Set Max Plasma Temp");
      debugln("t - Set Max Transformer Temp");
    }

};
