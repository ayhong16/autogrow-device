#include <DHT.h>
#include <vector>

#define DHT0PIN 6
#define DHT1PIN 7
#define DHTTYPE DHT11

struct Reading
{
    float temp;
    float humd;
    int error;

    Reading(float t, float h) : temp(t), humd(h), error(0) {}
    Reading(float t, float h, int err) : temp(t), humd(h), error(err) {}
};

class DHTSensor
{
public:
    DHTSensor(bool isFahrenheit = false);
    ~DHTSensor(){};

    Reading getSensorData();

private:
    Reading readOneSensor(int sensorIndex);
    void safeRead();
    float humidity;
    float temperature;
    bool isFahrenheit;
    std::vector<DHT> dhtSensors;
};