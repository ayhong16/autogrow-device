#include "ph.h"

/*
 * file read_ph.ino
 * @ https://github.com/GreenPonik/DFRobot_ESP_PH_WITH_ADC_BY_GREENPONIK
 *
 * IMPORTANT : to make it work, you will need the help of an additionnal ADC converter because the one on the ESP32 isn't accurate enough. Here we used an ADS1115 from Adafruit
 * You can find it here : https://www.adafruit.com/product/1085
 * And here is the library you'll need to add to your sketch : https://github.com/adafruit/Adafruit_ADS1X15
 *
 * This is the sample code for Gravity: Analog pH Sensor / Meter Kit V2, SKU:SEN0161-V2
 * In order to guarantee precision, a temperature sensor such as DS18B20 is needed, to execute automatic temperature compensation.
 * You can send commands in the serial monitor to execute the calibration.
 * Serial Commands:
 *   enterph -> enter the calibration mode
 *   calph   -> calibrate with the standard buffer solution, two buffer solutions(4.0 and 7.0) will be automaticlly recognized
 *   exitph  -> save the calibrated parameters and exit from calibration mode
 *
 * Based on the @ https://github.com/DFRobot/DFRobot_PH
 * Copyright   [DFRobot](http://www.dfrobot.com), 2018
 * Copyright   GNU Lesser General Public License
 *
 * ##################################################
 * ##################################################
 * ######## Forked on github by GreenPonik ##########
 * ############# ONLY ESP COMPATIBLE ################
 * ##################################################
 * ##################################################
 *
 * version  V1.2.2
 * date  2019-06
 */

#define PIN_SDA 20
#define PIN_SCL 21

PHSensor::PHSensor()
{
  Serial.println("PH Sensor constructor");
  EEPROM.begin(32);
  Serial.println("EEPROM initialized");
  ph.begin(0);
  Serial.println("PH Sensor initialized");
  Serial.println("Wire initialized");
  // ads.begin();
  // ads.setGain(1);
}

float PHSensor::getPH(float temperature)
{
  safeRead(temperature);
  return phValue;
}

void PHSensor::safeRead(float temperature)
{
  int sensorValue = analogRead(A0); // Read analog voltage from pin A0
  float voltage = sensorValue / 4095.0 * 3.3;

  phValue = ph.readPH(voltage, temperature); // convert voltage to pH with temperature compensation
}

// void PHSensor::calibrate()
// {
//   ph.calibration(voltage, temperature); // calibration process by Serail CMD
// }