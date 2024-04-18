// Unofficial library: https://github.com/ropg/heltec_esp32_lora_v3/

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
float temperature = 25;
float humidity = 50;
char *name;

void syncState()
{
    State state = httpClient->getState();
    name = (char *)state.name.c_str();
    light.setState(state.light);
    phSensingInterval = state.dhtPollInterval;
    dhtSensingInterval = state.dhtPollInterval;

    display_values(temperature, humidity, phValue, name);
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
    delay(500);
    Heltec.display->flipScreenVertically();
    Heltec.display->clear();
    Heltec.display->flush();
    Heltec.display->setFont(ArialMT_Plain_10);
    light = Light();
    dht11 = DHTSensor();
    ph = PHSensor();
    WiFiWrapper();
    httpClient = make_unique<HTTPWrapper>();
    httpClient->testConnection();

    // Set initial values
    Reading dhtData = dht11.getSensorData();
    temperature = dhtData.temp;
    humidity = dhtData.humd;
    phValue = ph.getPH(temperature);
    syncState();
}

void loop()
{
    static unsigned long dhtSensingTimepoint = millis();
    static unsigned long phSensingTimepoint = millis();
    static unsigned long lightTimepoint = millis();
    if (millis() - dhtSensingTimepoint > dhtSensingInterval)
    {
        dhtSensingTimepoint = millis();
        Reading dhtData = dht11.getSensorData();
        temperature = dhtData.temp;
        humidity = dhtData.humd;
    }
    if (millis() - phSensingTimepoint > phSensingInterval)
    {
        phSensingTimepoint = millis();
        phValue = ph.getPH(temperature);
    }
    if (millis() - lightTimepoint > DEFAULT_STATE_INTERVAL)
    {
        lightTimepoint = millis();
        syncState();
    }

    ph.calibrate(ph.getVoltage(), dht11.getSensorData().temp);
}