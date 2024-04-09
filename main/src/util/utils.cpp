#include "utils.h"

void display_values(float temp, float humd, float phValue)
{
  Heltec.display->clear();
  struct tm timeinfo;
  if (getLocalTime(&timeinfo))
  {
    String str = "-- ";
    char buffer[20]; // Buffer to hold the formatted time string
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d",
            timeinfo.tm_mon + 1,     // Month, 0-based, so +1
            timeinfo.tm_mday,        // Day of the month
            timeinfo.tm_year + 1900, // Year since 1900
            timeinfo.tm_hour,        // Hour
            timeinfo.tm_min,         // Minute
            timeinfo.tm_sec);        // Second
    Serial.println(buffer);
    str += buffer;
    str += " --";
    print_string(str, 0);
  }
  else
  {
    Serial.println("Failed to obtain time");
  }
  print_string("Temperature: " + String(temp) + "°C", 12);
  print_string("Humidity: " + String(humd) + "%", 24);
  print_string("pH: " + String(phValue), 36);
}

void print_string(const String &str, int yHeight)
{
  Serial.println(str);
  // display.println(str);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  // Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, yHeight, str);
  Heltec.display->display();
}