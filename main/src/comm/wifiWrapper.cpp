#include "wifiWrapper.h"

WiFiWrapper::WiFiWrapper()
{
    Serial.println();
    Serial.println("Booting Sketch...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASS);
    while (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Connecting...");
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    configTzTime("EST5EDT,M3.2.0,M11.1.0",
                 "pool.ntp.org",
                 "time.nist.gov");
    Serial.println("Time synchronized");
}