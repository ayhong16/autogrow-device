// Unofficial library: https://github.com/ropg/heltec_esp32_lora_v3/

#include "src/sensor/dht11.h"
// #include "src/sensor/ph.h"
#include "src/actuator/light.h"
#include "src/comm/wifiWrapper.h"
#include "src/comm/httpWrapper.h"
#include <heltec.h>
#include <memory>

Light light;
DHTSensor dht11;
// PHSensor ph;
std::unique_ptr<HTTPWrapper> httpClient;

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void setup()
{
    heltec_setup();
    light = Light();
    dht11 = DHTSensor();
    // ph = PHSensor();
    WiFiWrapper();
    httpClient = make_unique<HTTPWrapper>();
    httpClient->testConnection();
}

void loop()
{
    heltec_loop();
    delay(5000);
    light.toggle();
    Reading dhtData = dht11.getSensorData();
    // float phValue = ph.getPH();
    float phValue = 0;
    float t = dhtData.temp;
    float h = dhtData.humd;
    display_values(t, h, phValue);
    int response_code = httpClient->postMeasurements(t, h, phValue, false);
    if (response_code >= 0)
    {
        Serial.println("Upload to server successful");
    }
    else
    {
        Serial.println("Failed to upload to server");
    }
}

void display_values(float temp, float humd, float phValue)
{
    display.cls();
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        both.print("-- ");
        both.print(&timeinfo, "%B %d %Y %H:%M:%S");
        both.println(" --");
    }
    else
    {
        Serial.println("Failed to obtain time");
    }
    both.println("Temperature: " + String(temp) + "°C");
    both.println("Humidity: " + String(humd) + "%");
    both.println("pH: " + String(phValue));
}