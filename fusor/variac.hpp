#pragma once

//#include <Tic.h>
#include <JrkG2.h>
#include <PID_v1.h>

#include "settings.hpp"
#include "pins.hpp"
#include "sensors.hpp"  // variac voltage needed to drive the PID

class _Variac {
  public:

    _Variac(): myPID(&input, &output, &setpoint, settings.structure.motorP, settings.structure.motorI, settings.structure.motorD, DIRECT) {}

    void begin() {
      pinMode(VARIAC_RELAY, OUTPUT);
      digitalWrite(VARIAC_RELAY, LOW);
      myPID.SetMode(AUTOMATIC);   //set PID in Auto mode
      myPID.SetSampleTime(100);  // refresh rate of PID controller
      // myPID.SetOutputLimits(-2000, 2000);    // TIC T249 max velocity
      myPID.SetOutputLimits(-100, 100);    // JRK 24v19 max pwm
      setPID();
      debugln("Variac setup complete");
    }

    void enable(bool on = true) {
      enabled = on;
    }

    void disable() {
      enabled = false;
    }

    void setPID() {
      myPID.SetTunings(settings.structure.motorP, settings.structure.motorI, settings.structure.motorD);
      debugln("P:", settings.structure.motorP, "I:", settings.structure.motorI, "D:", settings.structure.motorD, "Updated");
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
        // tic.exitSafeStart();
        variacRelayState = 1;
        // Limit the input voltage
        if (setpoint > settings.structure.maxVariacVoltage) {
          setpoint = settings.structure.maxVariacVoltage;
        }
        // Update current and voltage values
        if (Timer.variac(100)) {
          input = Sensors.getVariacVoltage();
          current = Sensors.getVariacCurrent();
        }
        myPID.Compute();
        if (input == setpoint) {
          // tic.setTargetVelocity(0);
          jrk.stopMotor();
        }
        else {
          //tic.setTargetVelocity(output * 1000);
          jrk.forceDutyCycle(output * -1);
        }

        // Handle Alarms
        error = abs(input - setpoint);
        if (error > settings.structure.maxMotorError) {
          // Alarm.raise(VARIAC_MOTOR_ERROR);  // Motor cannot keep up with PID
        }
        if (Sensors.getVariacCurrent() > settings.structure.maxVariacCurrent) {
          //  Alarm.raise(VARIAC_OVERCURRENT);
        }
        if (printVariac) {
          debugln(input, setpoint, output, error);
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

  public:
    PID myPID;
    //TicI2C tic;
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
