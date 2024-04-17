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
}

void loop()
{
    static unsigned long timepoint = millis();
    if (millis() - timepoint > 2500U) // time interval: 5s
    {
        timepoint = millis();
        light.toggle();
        Reading dhtData = dht11.getSensorData();
        float phValue = ph.getPH(dhtData.temp);

        display_values(dhtData.temp, dhtData.humd, phValue);
        int response_code = httpClient->postMeasurements(dhtData.temp, dhtData.humd, phValue, false);
        if (response_code >= 0)
        {
            Serial.println("Upload to server successful");
        }
        else
        {
            Serial.println("Failed to upload to server");
        }
    }

    ph.calibrate(ph.getVoltage(), dht11.getSensorData().temp);
}