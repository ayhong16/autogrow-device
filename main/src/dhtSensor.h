#include <DHT.h>

#define DHTPIN 7
#define DHTTYPE DHT11

class dhtSensor
{
public:
    dhtSensor(bool isFahrenheit = false);
    ~dhtSensor(){};

    int readTemperature();
    int readHumidity();
    void init();

private:
    void readSensorData();
    int lastReadingTimestamp;
    int humidity;
    int temperature;
    bool isFahrenheit;
    DHT dht;
};