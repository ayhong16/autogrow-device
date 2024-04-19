#include "ph.h"

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