// https://github.com/GreenPonik/DFRobot_ESP_PH_WITH_ADC_BY_GREENPONIK

#include <Arduino.h>
#include "../lib/PH Sensor/DFRobot_ESP_PH_WITH_ADC.h"
#include <iostream>
#include <list>
#include <algorithm>
#include <iterator>
#include <Wire.h>
#include <EEPROM.h>

#define PH_PIN GPIO_NUM_1
class PHSensor
{
public:
  PHSensor();
  ~PHSensor(){};

  float getPH(float temperature);
  float getVoltage();
  void calibrate(float voltage, float temperature);

private:
  float voltage, phValue, temperature = 25;
  DFRobot_ESP_PH_WITH_ADC ph;
  // ADS1115 ads;
};