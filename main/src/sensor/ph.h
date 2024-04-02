// https://github.com/GreenPonik/DFRobot_ESP_PH_WITH_ADC_BY_GREENPONIK

// #include "../lib/DFRobot_PH/DFRobot_PH.h"
// #include <EEPROM.h>

#define PH_PIN GPIO_NUM_1
class PHSensor
{
public:
  PHSensor();
  ~PHSensor(){};

  float getPH();
  // void calibrate();

private:
  float voltage, phValue, temperature = 25;
  // DFRobot_PH ph;

  void safeRead();
};