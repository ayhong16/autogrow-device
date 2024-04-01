#include "dhtSensor.h"

DHTSensor::DHTSensor(bool isFahrenheit)
{
    std::vector<std::pair<int, int>> sensorConfigs = {
        {DHT0PIN, DHTTYPE},
        {DHT1PIN, DHTTYPE}};

    for (const auto &config : sensorConfigs)
    {
        DHT sensor(config.first, config.second);
        sensor.begin();
        dhtSensors.push_back(sensor);
    }
    humidity = 0;
    temperature = 0;
    isFahrenheit = isFahrenheit;
}

float DHTSensor::readTemperature()
{
    readOneSensor(0);
    return temperature;
}

int DHTSensor::readHumidity()
{
    readOneSensor(0);
    return humidity;
}

Reading DHTSensor::readOneSensor(int sensorIndex)
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dhtSensors[sensorIndex].readHumidity();
    float t = dhtSensors[sensorIndex].readTemperature(false);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    return Reading(t, h);
}

void DHTSensor::safeRead()
{
    int i = 0;
    while (i < dhtSensors.size())
    {
        Reading sensorReading = readOneSensor(i);
        i++;
    }
}