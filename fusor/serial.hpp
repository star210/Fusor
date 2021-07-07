#pragma once

#include "motor.hpp"

void process_serial() {
  char cmd = Serial.read();
  if (cmd > 'Z') cmd -= 32;
  switch (cmd) {
    case 'P': kp = Serial.parseFloat(); myPID.SetTunings(kp, ki, kd); break;
    case 'D': kd = Serial.parseFloat(); myPID.SetTunings(kp, ki, kd); break;
    case 'I': ki = Serial.parseFloat(); myPID.SetTunings(kp, ki, kd); break;
    case 'Q': Serial.print("P: "); Serial.print(kp); Serial.print(" I: "); Serial.print(ki); Serial.print(" D: "); break;
    case 'W': writetoEEPROM(); break;
    case 'R': pumpRelayState = !pumpRelayState; break; // toggle relay state
    case 'N': variacRelayState = !variacRelayState; break; // toggle relay state
    case 'V': setVoltage = Serial.parseInt(); Serial.print("Variac voltage set to: "); Serial.print(setVoltage); break;
    case 'N': sensorSerialPrint = !sensorSerialPrint; break; // toggle relay state   
    case 'H': help(); break;
    case 'K': eedump(); break;
  }
  while (Serial.read() != 10); // dump extra characters till LF is seen (you can use CRLF or just LF)
}

void help() {
  Serial.println(F("\nPID DC motor controller and stepper interface emulator"));
  Serial.println(F("P123.45 sets proportional term to 123.45"));
  Serial.println(F("I123.45 sets integral term to 123.45"));
  Serial.println(F("D123.45 sets derivative term to 123.45"));
  Serial.println(F("Q will print out the current values of P, I and D parameters"));
  Serial.println(F("W will store current values of P, I and D parameters into EEPROM"));
  Serial.println(F("R will toggle on/off vacuum pump relay"));
  Serial.println(F("N will toggle on/off variac output relay"));
  Serial.println(F("V sets variac output voltage"));
  Serial.println(F("S will toggle on/off sensor readout"));
  Serial.println(F("H will print this help message again"));
}
