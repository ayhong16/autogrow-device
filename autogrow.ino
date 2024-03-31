// Unofficial library: https://github.com/ropg/heltec_esp32_lora_v3/

#include <heltec.h>

#include "src/dhtSensor.h"
#include "src/wifi.h"

dhtSensor dht11;
Wifi wifi;

void setup() {
    heltec_setup();
    dht11.init();
    dht11 = dhtSensor(true);
    delay(2000);  // Delay to let system boot up.
    // wifi = Wifi();
}

void loop() {
    heltec_loop();
    delay(5000);  // Delay between measurements.
    float h = dht11.readHumidity();
    float t = dht11.readTemperature();
    display.println("Humidity: " + String(h) + "%");
    display.println("Temperature: " + String(t) + "°C");
}