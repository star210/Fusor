#pragma once

#include <JrkG2.h>
#include <PID_v1.h>

#include "settings.hpp"
#include "pins.hpp"
#include "sensors.hpp"  // variac voltage needed to drive the PID

class _Variac {
  public:

    _Variac(): myPID(&input, &output, &setpoint, settings.motorP, settings.motorI, settings.motorD, DIRECT) {}

    void begin() {
      pinMode(VARIAC_RELAY, OUTPUT);
      digitalWrite(VARIAC_RELAY, LOW);
      myPID.SetMode(AUTOMATIC);   //set PID in Auto mode
      myPID.SetSampleTime(100);  // refresh rate of PID controller
      myPID.SetOutputLimits(800, 2200);    // JRK 24v19 max pwm
      setPID();
      delay(100);
      debugln("Variac setup complete");
    }

    void enable(bool on = true) {
      enabled = on;
    }

    void disable() {
      enabled = false;
    }

    void setPID() {
      myPID.SetTunings(settings.motorP, settings.motorI, settings.motorD);
      debugln("P:", settings.motorP, "I:", settings.motorI, "D:", settings.motorD, "Updated");
    }

    void turnRelayOn(bool on = true) {
      variacRelayState = on;
    }

    bool setVoltage (int voltage, int stepTime) {
      auto now = millis();
      if (now - lastTime > stepTime) {
        lastTime = now;
        if (setpoint < voltage) {
          setpoint ++;
          return false;
        }
        if (setpoint > voltage) {
          setpoint --;
          return false;
        }
        if (setpoint == voltage)
          return true;
      }
      return false;
    }

    void update() {
      if (enabled) {
        variacRelayState = 1;

        // Update current and voltage values
        if (Timer.variac(100)) {
          // Limit the input voltage
          if (setpoint > settings.maxVariacVoltage) {
            setpoint = settings.maxVariacVoltage;
          }
          input = Sensors.getVariacVoltage();
          current = Sensors.getVariacCurrent();
          // Compute PID
          myPID.Compute();
          if (input == setpoint) {
            jrk.stopMotor();
          }
          else {
            jrk.forceDutyCycle(output * -1);
            //  debugln("Pololu output:", output);
            // jrk.forceDutyCycle(output);
            delay(50);
          }

          // Handle Alarms
          error = abs(input - setpoint);
          if (error > settings.maxMotorError) {
            Alarm.raise(VARIAC_MOTOR_ERROR);  // Motor cannot keep up with PID
          }
          if (Sensors.getVariacCurrent() > settings.maxVariacCurrent) {
            Alarm.raise(VARIAC_OVERCURRENT);
          }
        }
      }
      else {
        variacRelayState = 0;
      }
      digitalWrite(VARIAC_RELAY, variacRelayState);  // update relay state
    }


    bool Print() {

      return printVariac;
    }

    void Toggle() {
      printVariac = ! printVariac;
    }

    void printMotor() {
      debugln("Enabled:", enabled, "Input:", input, "Setpoint:", setpoint, "Output:", output, "Error:", error);
    }

  public:
    PID myPID;
    JrkG2I2C jrk;
    double input = 0, output = 0, setpoint = 0, error = 0;
    double kp, ki, kd;
    double current;

    uint32_t lastTime = 0;
    bool printVariac = false;
    bool enabled = false;
    bool variacRelayState = false; // bool to store relay state
};

extern _Variac Variac;
