#include <heltec.h>

#include "src/dhtSensor.h"

dhtSensor dht11 = dhtSensor(true);

void setup() {
    heltec_setup();
    dht11.init();
}

void loop() {
    heltec_loop();
    delay(2000);  // Delay between measurements.
    float h = dht11.readHumidity();
    float t = dht11.readTemperature();
    display.println("Humidity: " + String(h) + "%");
    display.println("Temperature: " + String(t) + "°C");
}