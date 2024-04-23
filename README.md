# AutoGrow Device

AutoGrow is a partially automated, smart hydroponic system that allows users to view pH levels, temperatures, and humidity values in realtime from anywhere. It also collects and displays historical data with live updating so that users can view previous trends in order to learn and optimize their hydroponic systems. AutoGrow is also a proof of concept that hydroponics can be automated by implementing an automatic grow light scheduler.

This is 1 of 2 repositories relating to the final project for ECE 590: Full Stack IoT at Duke University. This repository contains the code for the Heltec ESP32 Lora V3 microcontroller.

## Development Instructions

1. Add both of these links to additional board urls:
   1. <https://ropg.github.io/heltec_boards/boards.json>
   2. <https://espressif.github.io/arduino-esp32/package_esp32_index.json>
2. Open *Arduio board manager*
3. Refresh package indexes
4. Search for and install **Heltec (unofficial)**
5. Open *Arduino library manager*
6. Install the following packages
   1. **Heltec_ESP32_LoRa_v3**
   2. **DHT sensor library**
   3. **DFRobot_ESP_PH_WITH_ADC_BY_GREENPONIK**
7. Set board type to **ESP32 LoRa v3 (Heltec (unofficial))**
8. Copy `main/src/secrets.h.example` to `secrets.h` and fill out information
