// Unofficial library: https://github.com/ropg/heltec_esp32_lora_v3/

#include <heltec.h>
#include "src/dhtSensor.h"
#include "src/wifiWrapper.h"
#include "src/httpWrapper.h"
#include <memory>

DHTSensor dht11;
std::unique_ptr<HTTPWrapper> httpClient;

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void setup()
{
    heltec_setup();
    dht11 = DHTSensor(false);
    WiFiWrapper();
    httpClient = make_unique<HTTPWrapper>();
    httpClient->testConnection();
}

void loop()
{
    heltec_loop();
    delay(30000);
    Reading dhtData = dht11.getSensorData();
    float t = dhtData.temp;
    float h = dhtData.humd;
    display_values(t, h);
    int response_code = httpClient->postMeasurements(t, h, 4.69, false);
    if (response_code >= 0)
    {
        display.println("Upload to server successful");
    }
    else
    {
        display.println("Failed to upload to server");
    }
}

void display_values(float temp, float humd)
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
    both.println("Humidity: " + String(humd) + "%");
    both.println("Temperature: " + String(temp) + "°C");
}