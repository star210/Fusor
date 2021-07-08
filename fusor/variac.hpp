#pragma once

#include <PID_v1.h>
#include "pins.hpp"
#include "adc.hpp"  // variac voltage needed to drive the PID

#define PWM_FREQUENCY 30000;      // 30khz pwm frequency 
#define PWM_RESOUTION 8;          // 8 bit resolution (1 - 16)
#define PWM_CHANNEL_1 0;
#define PWM_CHANNEL_2 1;

#define MAX_VOLTAGE 100; // Max output voltage limit in volts

double kp = 0, ki = 0, kd = 0.0;
double input = 0, output = 0, setpoint = 0;
PID myPID(&input, &output, &setpoint, kp, ki, kd, DIRECT);

bool variacRelayState = 0; // bool to store relay state
int setVoltage = 0;  

void setup() {

  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);

  pinMode(HIGH_VOLTAGE_RELAY, OUTPUT);
  digitalWrite(HIGH_VOLTAGE_RELAY, LOW);

  ledcSetup(PWM_CHANNEL, PWM_FREQUENCY, PWM_RESOUTION);
  ledcAttachPin(M1, PWM_CHANNEL_1);
  ledcAttachPin(M2, PWM_CHANNEL_2);

  recoverPIDfromEEPROM();

  myPID.SetMode(AUTOMATIC);   //set PID in Auto mode
  myPID.SetSampleTime(1);  // refresh rate of PID controller
  myPID.SetOutputLimits(-125, 125); // this is the MAX PWM value to move motor, here change in value reflect change in speed of motor.
  Serial.println("Motor setup complete");
}
void update() {

  digitalWrite(HIGH_VOLTAGE_RELAY, variacRelayState);  // update relay state

  input = VariacVoltage;       // Voltage readout in Volts from variac voltage sensor
  setpoint = setVoltage  // Set voltage 
  
    while (!myPID.Compute())
        if (input == setpoint)pwmOut(0); else pwmOut(output);    // only move motor when needed
        if (setVoltage > MAX_VOLTAGE) setVoltage = MAX_VOLTAGE;  // limit output voltage
}

void pwmOut(int out) {
  if (out < 0) {
    ledcWrite(M1, 0);
    ledcWrite(M2, abs(out));
  }
  else {
    ledcWrite(M2, 0);
    ledcWrite(M1, abs(out));
  }
}

void writetoEEPROM() { // keep PID set values in EEPROM so they are kept when arduino goes off
  eeput(kp, 0);
  eeput(ki, 4);
  eeput(kd, 8);
  double cks = 0;
  for (int i = 0; i < 12; i++) cks += EEPROM.read(i);
  eeput(cks, 12);
  Serial.println(F("PID values stored to EEPROM"));
  //Serial.println(cks);
}
void recoverPIDfromEEPROM() {
  double cks = 0;
  double cksEE;
  for (int i = 0; i < 12; i++) cks += EEPROM.read(i);
  cksEE = eeget(12);
  //Serial.println(cks);
  if (cks == cksEE) {
    Serial.println(F("Found PID values on EEPROM"));
    kp = eeget(0);
    ki = eeget(4);
    kd = eeget(8);
    myPID.SetTunings(kp, ki, kd);
  }
  else Serial.println(F("Bad EEPROM checksum"));
}

void eedump() {
  for (int i = 0; i < 16; i++) {
    Serial.print(EEPROM.read(i), HEX);
    Serial.print(" ");
  } Serial.println();
}
