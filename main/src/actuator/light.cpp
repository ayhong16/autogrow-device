#include "light.h"

Light::Light()
{
  isOn = false;
  pinMode(LIGHT_PIN, OUTPUT);
}

void Light::turnOn()
{
  digitalWrite(LIGHT_PIN, HIGH);
  isOn = true;
}

void Light::turnOff()
{
  digitalWrite(LIGHT_PIN, LOW);
  isOn = false;
}

void Light::toggle()
{
  if (isOn)
  {
    turnOff();
  }
  else
  {
    turnOn();
  }
}

void Light::setState(bool state)
{
  if (state)
  {
    turnOn();
  }
  else
  {
    turnOff();
  }
}

bool Light::getState()
{
  return isOn;
}