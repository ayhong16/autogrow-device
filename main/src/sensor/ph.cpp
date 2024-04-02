#include "ph.h"

PHSensor::PHSensor()
{
  // ph.begin();
}

float PHSensor::getPH()
{
  return phValue;
}

void PHSensor::safeRead()
{
  // voltage = analogRead(PH_PIN) / 1024.0 * 5000; // read the voltage
  // phValue = ph.readPH(voltage, temperature);    // convert voltage to pH with temperature compensation
  phValue = 0;
}

// void PHSensor::calibrate()
// {
//   ph.calibration(voltage, temperature); // calibration process by Serail CMD
// }