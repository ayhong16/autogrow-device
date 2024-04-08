// https://github.com/GreenPonik/DFRobot_ESP_PH_WITH_ADC_BY_GREENPONIK

// #include "../lib/DFRobot_PH/DFRobot_PH.h"
// #include <EEPROM.h>

#include "../lib/PH Sensor/DFRobot_ESP_PH_WITH_ADC.h"
#include <Adafruit_ADS1X15.h>
#include <EEPROM.h>

#define PH_PIN GPIO_NUM_1
class PHSensor
{
public:
  PHSensor();
  ~PHSensor(){};

  float getPH(float temperature);

private:
  float voltage, phValue, temperature = 25;
  DFRobot_ESP_PH_WITH_ADC ph;
  Adafruit_ADS1115 ads;

  void safeRead(float temperature);
};