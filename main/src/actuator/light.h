#include "arduino.h"

#define LIGHT_PIN GPIO_NUM_19

class Light
{
public:
  Light();
  ~Light(){};

  void turnOn();
  void turnOff();
  void toggle();

private:
  bool isOn;
};