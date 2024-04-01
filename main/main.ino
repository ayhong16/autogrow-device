// Unofficial library: https://github.com/ropg/heltec_esp32_lora_v3/

#include <heltec.h>
#include "src/dhtSensor.h"
#include "src/wifiWrapper.h"
#include "src/httpWrapper.h"
#include <memory>

dhtSensor dht11;
std::unique_ptr<HTTPWrapper> httpClient;

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void setup()
{
    heltec_setup();
    dht11.init();
    dht11 = dhtSensor(true);
    WiFiWrapper();
    httpClient = make_unique<HTTPWrapper>();
    httpClient->testConnection();
}

void loop()
{
    heltec_loop();
    delay(5000); // Delay between measurements.
    float h = dht11.readHumidity();
    float t = dht11.readTemperature();
    display_values(t, h);
    httpClient->postMeasurements(5.5, 5.0, 4.69, false);
}

void display_values(float temp, float humd)
{
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