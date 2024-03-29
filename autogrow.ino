#include <heltec.h>

void setup() {
    heltec_setup();
}

int i = 0;

void loop() {
    heltec_loop();

    Serial.println("Serial works");
    display.println("Display works " + String(i++));
    delay(1000);
}