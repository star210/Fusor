#pragma once

#include <Adafruit_ADS1015.h>

#include "util.hpp"

// 3.3k - 2.2k resistor divider 10v in 4v out - adc volts x 2.5
// ads1115 15bit resolution ADS1115 - 32768

#define NUM_P_LUT 47
const float P_LUT[NUM_P_LUT][2] = {
  { 2, 0.00000075 },
  { 2.05, 0.000062 },
  { 2.1, 0.00017 },
  { 2.2, 0.000375 },
  { 2.4, 0.00081 },
  { 2.6, 0.00126 },
  { 2.8, 0.00195 },
  { 3, 0.00288 },
  { 3.2, 0.00386 },
  { 3.4, 0.00515 },
  { 3.6, 0.00788 },
  { 3.8, 0.0117 },
  { 4, 0.0158 },
  { 4.2, 0.0208 },
  { 4.4, 0.0259 },
  { 4.6, 0.0312 },
  { 4.8, 0.0378 },
  { 5, 0.0444 },
  { 5.2, 0.0656 },
  { 5.4, 0.0953 },
  { 5.6, 0.128 },
  { 5.8, 0.167 },
  { 6, 0.218 },
  { 6.2, 0.268 },
  { 6.4, 0.326 },
  { 6.6, 0.4 },
  { 6.8, 0.48 },
  { 7, 0.575 },
  { 7.2, 0.692 },
  { 7.4, 0.855 },
  { 7.6, 1.05 },
  { 7.8, 1.25 },
  { 8, 1.44 },
  { 8.2, 1.79 },
  { 8.4, 2.21 },
  { 8.6, 2.63 },
  { 8.8, 3.13 },
  { 9, 4.05 },
  { 9.2, 5.3 },
  { 9.4, 7.27 },
  { 9.5, 9.68 },
  { 9.6, 12.4 },
  { 9.7, 15.5 },
  { 9.8, 25.4 },
  { 9.9, 47.4 },
  { 9.95, 108 },
  { 10, 750 }
};

class _Sensors {
  public:
    _Sensors(): ads1(0x48), ads2(0x49) {}

    void begin() {
      ads1.begin();
      ads2.begin();

      ads1.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV (default)
      //      ads1.setGain(GAIN_ONE);     // 1x gain   +/- 4.096V  1 bit = 2mV
      //      ads2.setGain(GAIN_TWO);     // 2x gain for an input range of +/-2.048V)
      debugln("ADC setup complete");
    }

    double getVacuumPressure() {
      int raw = ads1.readADC_SingleEnded(0);
      float voltage = raw / 2125.00; // between 0 and 10;
      //  debugln("Vaccuum Voltage: ", voltage, "volts  Raw ADC:", raw);

      // find the two points the voltage is inside and linearly interpolate
      for (int i = 1; i < NUM_P_LUT; i++) {
        float a = P_LUT[i - 1][0];
        float b = P_LUT[i][0];
        if (voltage >= a && voltage < b) {
          return vmap(voltage, a, b, P_LUT[i - 1][1], P_LUT[i][1]);
        }
      }
      return 0;
    }

    double getVariacVoltage() {
      // 19385 / 264v = 73.4
      int raw = ads1.readADC_SingleEnded(1);
      // debugln("Variac Voltage: ", raw / 73.40, "volts  Raw ADC:", raw);
      if (raw == 65535) {
        return 0;
      }
      return raw / 73.40;
    }

    double getVariacCurrent() {
      // 18615 / 1.62A
      int raw = ads1.readADC_SingleEnded(2);
      //   debugln("Variac Current: ", raw / 11.49, "milliamps  Raw ADC:", raw);
      if (raw == 65535) {
        return 0;
      }
      return raw / 11.49;
    }

    double getHVVoltage() {
      // High Voltage 0 - 10000v
      // 32768 / 16000 = 2.048v 32000 / 16000 = 2v
      // 2v * 2.5 = 5v
      // 5v * 2000 = 10000v
      // 32000 / 3.2 = 10000v
      return ads2.readADC_SingleEnded(0) / 3.2;
    }

    double getHVCurrent() {
      // High Voltage 0 - 50mA
      // 32768 / 16000 = 2.048v 32000 / 16000 = 2v
      // 2v * 2.5 = 5v
      // 5v * 10 = 50mA
      // 32000 / 640 = 50mA
      return ads2.readADC_SingleEnded(1) / 640;
    }

    void scanAddress() {
  byte error, address;
  int nDevices = 0;
 
      for (address = 1; address < 127; address++ ) {
        Wire.beginTransmission(address);
        error = Wire.endTransmission();
        if (error == 0) {
          debug("I2C device found at address: ");
          if (address < 10) {
            debug("0");
          }
          debugln(address);
          nDevices++;
        }
        else if (error == 4) {
          debug("Unknown error at address:");
          if (address < 10) {
            debug("0");
          }
          debug(address, HEX);
        }
      }
      if (nDevices == 0) {
        debugln("No I2C devices found\n");
      }
    }
  public:
    Adafruit_ADS1115 ads1;      // 0 - 10v input
    Adafruit_ADS1115 ads2;      // 0 - 5v input
};

extern _Sensors Sensors;
