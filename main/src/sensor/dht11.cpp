#include "dht11.h"

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

Reading DHTSensor::getSensorData()
{
    safeRead();
    return Reading(temperature, humidity);
}

Reading DHTSensor::readOneSensor(int sensorIndex)
{
    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dhtSensors[sensorIndex].readHumidity();
    float t = dhtSensors[sensorIndex].readTemperature(false);

    Serial.println("Sensor " + String(sensorIndex) + " - Humidity: " + String(h) + " %\tTemperature: " + String(t) + " *C ");

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t))
    {
        Serial.println(F("Failed to read from DHT sensor!"));
        return Reading(0, 0, -1);
    }

    return Reading(t, h);
}

void DHTSensor::safeRead()
{
    float discrepency_threshold = 3;
    std::vector<Reading> sensorReadings;
    int i = 0;
    while (i < dhtSensors.size())
    {
        sensorReadings.push_back(readOneSensor(i));
        i++;
    }

    float avg_temp = 0;
    float avg_humd = 0;

    for (const auto reading : sensorReadings)
    {
        if (reading.error < 0)
        {
            return;
        }
        avg_humd += reading.humd;
        avg_temp += reading.temp;
    }

    avg_humd /= sensorReadings.size();
    avg_temp /= sensorReadings.size();

    for (const auto reading : sensorReadings)
    {
        if (abs(avg_humd - reading.humd) > discrepency_threshold || abs(avg_temp - reading.temp) > discrepency_threshold)
        {
            Serial.println("Error: Sensor discrepency detected");
            return;
        }
    }

    temperature = avg_temp;
    humidity = avg_humd;
}