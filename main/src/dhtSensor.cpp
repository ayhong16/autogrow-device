#include "dhtSensor.h"

dhtSensor::dhtSensor(bool isFahrenheit) : dht(DHTPIN, DHTTYPE) {
    humidity = 0;
    temperature = 0;
    isFahrenheit = isFahrenheit;
}

void dhtSensor::init() {
    dht.begin();
}

int dhtSensor::readTemperature() {
    readSensorData();
    return temperature;
}

int dhtSensor::readHumidity() {
    readSensorData();
    return humidity;
}

void dhtSensor::readSensorData() {
    int currentTimestamp = millis();
    if (lastReadingTimestamp / 1000 + 2 > currentTimestamp) {
        Serial.println("Too fast! Using old values...");
        return;
    }

    lastReadingTimestamp = millis();

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    float t = dht.readTemperature(false);

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
    }

    humidity = h;
    temperature = t;
}