#include "ph.h"

#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>

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

#define PH_4 2202.0
#define PH_7 1785.0

PHSensor::PHSensor()
{
  EEPROM.begin(32);
  Serial.println("EEPROM initialized");

  EEPROM.writeFloat(0, PH_7);
  EEPROM.writeFloat(sizeof(float), PH_4);

  // ads.begin();
  // ads.setGain(1);
  ph.begin(0);
  Serial.println("PH Sensor initialized");
}

float PHSensor::getPH(float temp)
{
  this->temperature = temp;

  const int averageCount = 50;
  std::list<float> _voltages;
  for (int i = 0; i < averageCount; i++)
  {
    float v = getVoltage();
    if (v <= 2500)
    {
      _voltages.push_back(v);
    }
    unsigned long loop_time = millis();
    while (millis() - loop_time < 20)
    {
      yield();
    }
  }
  _voltages.sort();
  auto median_voltage = _voltages.begin();
  std::advance(median_voltage, _voltages.size() / 2);
  this->voltage = *median_voltage;
  float average_voltage = 0;
  int count = 0;
  const float threshold = 150;
  for (auto v : _voltages)
  {
    if (v - *median_voltage > threshold || *median_voltage - v > threshold)
    {
      continue;
    }
    average_voltage += v;
    count++;
  }
  if (count > 0)
  {
    this->voltage = average_voltage / count;
    Serial.println("Average voltage: " + String(this->voltage) + "mV");
    this->phValue = ph.readPH(this->voltage, this->temperature);
  }
  return phValue;
}

float PHSensor::getVoltage()
{
  int sensorValue = analogRead(A0); // Read analog voltage from pin A0
  float mv = 1000 * sensorValue / 4095.0 * 3.0;
  return mv;
}

void PHSensor::calibrate(float v, float t)
{
  ph.calibration(v, t); // calibration process by Serail CMD
}