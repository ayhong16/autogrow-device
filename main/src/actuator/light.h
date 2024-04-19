#include "arduino.h"

#define LIGHT_PIN GPIO_NUM_19

class Light
{
public:
  Light();
  ~Light(){};

  void turnOn();
  void turnOff();
  void setState(bool state);
  bool getState();
  void toggle();

private:
  bool isOn = false;
};