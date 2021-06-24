# Fusor

NORVI IIOT-AE04-V2
https://norvi.lk/industrial-esp32-norvi-iiot/#IIOT_Models

Compile using "ESP32 Dev Module" 240mhz 


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Pinout

| Description          | Terminal | Cable Colour | Voltage        | GPIO     | Notes              |
|----------------------|----------|--------------|----------------|----------|--------------------|
| Variac Volts Input   | A0       | Blue         | 0-300V / 0-4v  | ADC1 CH0 |                    |
| Variac Amps Input    | A1       | Yellow       | 0-2A / 0-4v    | ADC1 CH1 |                    |
| NST Volts Input      | A2       | White        | 0-10kv / 0-4v  | ADC1 CH2 | 200M / 100K        |
| NST Amps Input       | A3       | Green        | 0-50mA / 0-4v  | ADC1 CH3 | 100ohm / 50mA / 5v |
| Vacuum Pressure      | A4       | White        | 2-8v /         | ADC2 CH0 |                    |
| Vacuum Pump Relay    | T0       | Yellow       | 24v            | GPIO26   |                    |
| Variac Relay         | T1       | Yellow       | 24v            | GPIO27   |                    |
| Plinth Safety Switch | I2       | Yellow       | 24v            | GPIO32   | Safety switch      |

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
STAGE 1 (No automation, control by simple web interface)

- OLED Displays important Wifi connection info and status
- Pump and Transformer relays Web ON/OFF button https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
- Web read out for all sensors in RAW and Volts 
- Web readout of mapped temp sensor 
- Web slider for variac PID input https://randomnerdtutorials.com/esp32-web-server-slider-pwm/
- Web readout of temp sensors https://randomnerdtutorials.com/esp32-ds18b20-temperature-arduino-ide/
- SD card to store CSS/HTML files https://randomnerdtutorials.com/esp32-web-server-microsd-card/
- Wifi manager Access Point using https://github.com/tzapu/WiFiManager

STAGE 2 (Automated standalone, remote monitoring)


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


