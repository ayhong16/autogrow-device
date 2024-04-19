#include "Arduino.h"
#include "heltec.h"
#include "src/util/utils.h"
#include "src/sensor/dht11.h"
#include "src/sensor/ph.h"
#include "src/actuator/light.h"
#include "src/comm/wifiWrapper.h"
#include "src/comm/httpWrapper.h"

Light light;
DHTSensor dht11;
PHSensor ph;
std::unique_ptr<HTTPWrapper> httpClient;
uint32_t phSensingInterval = DEFAULT_SENSING_INTERVAL;
uint32_t dhtSensingInterval = DEFAULT_SENSING_INTERVAL;

float phValue = 0;
float temperature = 0;
float humidity = 0;
char *name;

void getState()
{
    State state = httpClient->getState();
    if (state.err)
    {
        Serial.println("Failed to get state from server");
        return;
    }
    name = (char *)state.name.c_str();
    light.setState(state.light);

    // Sensing intervals are in seconds, convert to milliseconds
    phSensingInterval = state.phPollInterval * 1000;
    dhtSensingInterval = state.dhtPollInterval * 1000;

    display_values(temperature, humidity, phValue, name);
}

void postMeasurements()
{
    int response_code = httpClient->postMeasurements(temperature, humidity, phValue, light.getState());
    if (response_code >= 0)
    {
        Serial.println("Upload to server successful");
    }
    else
    {
        Serial.println("Failed to upload to server");
    }
}

void setup()
{
    Serial.begin(115200);
    Heltec.begin(true /*DisplayEnable Enable*/, false /*LoRa Disable*/, true /*Serial Enable*/);
    Heltec.display->flipScreenVertically();
    Heltec.display->clear();
    Heltec.display->setFont(ArialMT_Plain_10);
    light = Light();
    dht11 = DHTSensor();
    ph = PHSensor();
    WiFiWrapper();
    httpClient = make_unique<HTTPWrapper>();
    httpClient->testConnection();

    // Set initial values
    while (humidity == 0.0 || temperature == 0.0)
    {
        Reading dhtData = dht11.getSensorData();
        temperature = dhtData.temp;
        humidity = dhtData.humd;
        delay(2500);
        Serial.println("Waiting for sensor data...");
    }
    phValue = ph.getPH(temperature);
    getState();
}

void loop()
{
    bool post = false;
    static unsigned long dhtSensingTimepoint = millis();
    static unsigned long phSensingTimepoint = millis();
    static unsigned long lightTimepoint = millis();
    if (millis() - dhtSensingTimepoint > dhtSensingInterval)
    {
        dhtSensingTimepoint = millis();
        Reading dhtData = dht11.getSensorData();
        temperature = dhtData.temp;
        humidity = dhtData.humd;
        post = true;
    }
    if (millis() - phSensingTimepoint > phSensingInterval)
    {
        phSensingTimepoint = millis();
        phValue = ph.getPH(temperature);
        post = true;
    }
    if (millis() - lightTimepoint > DEFAULT_SYNC_INTERVAL)
    {
        lightTimepoint = millis();
        getState();
        httpClient->postMemory();
    }
    if (post)
    {
        postMeasurements();
    }
}