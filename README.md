# Fusor

NORVI IIOT-AE04-V2
https://norvi.lk/industrial-esp32-norvi-iiot/#IIOT_Models

Compile using "ESP32 Dev Module" 240mhz 

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

STAGE 1 (No automation, control by serial, No web interface yet)

- Serial displays all debug and status code
- OLED copys serial output?
- Pump and Transformer relays controlled with code
- Serial read out for all sensors mapped 
- Serial readout of pressure sensor using interpolated lookup table
- Auto variac motor PID program
- Serial readout of temp sensors 
- SD card test only
- OK / ALARM state reset via panel button 

STAGE 2 (Web monitoring, control by website)


- OLED Displays important Wifi connection info and status
- Pump and Transformer relays Web ON/OFF button https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
- Web read out for all sensors in RAW and Volts 
- Web readout of mapped pressure sensor using graph
- Web slider for variac PID input https://randomnerdtutorials.com/esp32-web-server-slider-pwm/
- Web readout of temp sensors https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/
- SD card to store CSS/HTML files https://randomnerdtutorials.com/esp32-web-server-microsd-card/
- Wifi manager Access Point using https://github.com/tzapu/WiFiManager
- OK / ALARM state that needs a reset button on webpage. OLED and Web to display ALARM code/reason


STAGE 3 (Automated standalone, remote monitoring)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Pinout

| Description        | Terminal | Cable Colour | Voltage        | Voltage Divider | GPIO     | Notes              |
|--------------------|----------|--------------|----------------|-----------------|----------|--------------------|
| Vacuum Pressure    | A0       | White        | 2-8v /         | 0.8-3.2v        | ADC1 CH0 |                    |
| Variac Volts Input | A1       | Blue         | 0-300V / 0-10v | 0-4v            | ADC1 CH1 |                    |
| Variac Amps Input  | A2       | Yellow       | 0-2A / 0-4v    | 0-4v            | ADC1 CH2 |                    |
| NST Volts Input    | A3       | White        | 0-10kv / 0-4v  | 0-2v GAIN 2     | ADC2 CH0 | 200M / 100K        |
| NST Amps Input     | A4       | Green        | 0-50mA / 0-4v  | 0-2v GAIN 2     | ADC2 CH1 | 100ohm / 50mA / 5v |
| Vacuum Pump Relay  | T0       | Yellow       | 24v            | GPIO26          |          |                    |
| Variac Relay       | T1       | Yellow       | 24v            | GPIO27          |          |                    |
| Safety Switch      | I2       | Yellow       | 24v            | GPIO34          |          |Safety switch       |

- Buttons on faceplate - GPIO32 analog input resistor ladder

IDC10 expansion connector pinout

| Description  | Terminal | Cable Colour | Voltage  | GPIO | Notes                |
|--------------|----------|--------------|----------|------|----------------------|
| DS18S20 Data | 1        | Yellow       | Data     | IO25 | Data for all sensors |
| DS18S20 3.3v | 7        | Red          | Power    | 3.3v |                      |
| Motor driver | 8        | Blue         | IN1      | IO17 | PWM                  |
| DS18S20 Gnd  | 9        | Black        | GND      | GND  |                      |
| Motor driver | 10       | Green        | IN2      | IO16 | PWM                  |


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Triggers that cause an ALARM state, switch OFF both pump and High Voltage relays. Wait for RESET on web

| Alarm Event                       | Description                                 | 
|-----------------------------------|---------------------------------------------|
| VACCUUM_PUMP_TEMP_MAX is reached  | Pump overheated                             | 
| PUMP_TIMEOUT is reached           | Seal leak causing it to never get to vacuum | 
| TRANSFORMER_TEMP_MAX              | Transformer overheated                      | 
| PLASMA_PLATE_TEMP_MAX is reached  | Plasma causing too much heat                |
| MIN_PRESSURE reached              | Cracked glass exposing HV element           |
| SAFETY_SWITCH trigger             | Removal of plinth cover vacuum ok but no HV |

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

| Settings                          | Description                                 | 
|-----------------------------------|---------------------------------------------|
| MAX_VOLTAGE         | Voltage input limit to variac                             |
| MAX_PRESSURE                      | Pressure to turn off vacuum pump            |

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Pressure sensor volts/pressure table

| Volts | Pressure (Torr) | Scientific Notation |
|-------|-----------------|---------------------|
| 2     | 0.00000075      | < 7.5 x 10e-7       |
| 2.05  | 0.000062        | 6.20 x 10e-5        |
| 2.1   | 0.00017         | 1.70 x 10e-4        |
| 2.2   | 0.000375        | 3.75 x 10e-4        |
| 2.4   | 0.00081         | 8.10 x 10e-4        |
| 2.6   | 0.00126         | 1.26 x 10e-3        |
| 2.8   | 0.00195         | 1.95 x 10e-3        |
| 3     | 0.00288         | 2.88 x 10e-3        |
| 3.2   | 0.00386         | 3.86 x 10e-3        |
| 3.4   | 0.00515         | 5.15 x 10e-3        |
| 3.6   | 0.00788         | 7.88 x 10e-3        |
| 3.8   | 0.0117          | 1.17 x 10e-2        |
| 4     | 0.0158          | 1.58 x 10e-2        |
| 4.2   | 0.0208          | 2.08 x 10e-2        |
| 4.4   | 0.0259          | 2.59 x 10e-2        |
| 4.6   | 0.0312          | 3.12 x 10e-2        |
| 4.8   | 0.0378          | 3.78 x 10e-2        |
| 5     | 0.0444          | 4.44 x 10e-2        |
| 5.2   | 0.0656          | 6.56 x 10e-2        |
| 5.4   | 0.0953          | 9.53 x 10e-2        |
| 5.6   | 0.128           | 1.28 x 10e-1        |
| 5.8   | 0.167           | 1.67 x 10e-1        |
| 6     | 0.218           | 2.18 x 10e-1        |
| 6.2   | 0.268           | 2.68 x 10e-1        |
| 6.4   | 0.326           | 3.26 x 10e-1        |
| 6.6   | 0.4             | 4.00 x 10e-1        |
| 6.8   | 0.48            | 4.80 x 10e-1        |
| 7     | 0.575           | 5.75 x 10e-1        |
| 7.2   | 0.692           | 6.92 x 10e-1        |
| 7.4   | 0.855           | 8.55 x 10e-1        |
| 7.6   | 1.05            | 1.05                |
| 7.8   | 1.25            | 1.25                |
| 8     | 1.44            | 1.44                |
| 8.2   | 1.79            | 1.79                |
| 8.4   | 2.21            | 2.21                |
| 8.6   | 2.63            | 2.63                |
| 8.8   | 3.13            | 3.13                |
| 9     | 4.05            | 4.05                |
| 9.2   | 5.3             | 5.3                 |
| 9.4   | 7.27            | 7.27                |
| 9.5   | 9.68            | 9.68                |
| 9.6   | 12.4            | 1.24 x 10e1         |
| 9.7   | 15.5            | 1.55 x 10e1         |
| 9.8   | 25.4            | 2.54 x 10e1         |
| 9.9   | 47.4            | 4.74 x 10e1         |
| 9.95  | 108             | 1.08 x 10e2         |
| 10    | 750             | 7.50 x 10e2         |

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



