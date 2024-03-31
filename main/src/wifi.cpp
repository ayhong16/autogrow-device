#include "wifi.h"

#define SSID "TheFruit"
#define PASS "rollshoots"

Wifi::Wifi() {
    Serial.print("Connecting to ");
    Serial.println(SSID);

    WiFi.begin(SSID, PASS);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
}