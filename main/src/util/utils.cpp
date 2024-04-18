#include "utils.h"

#define LINE_HEIGHT 12

void display_values(float temp, float humd, float phValue, char *name)
{
  Heltec.display->clear();
  struct tm timeinfo;
  if (getLocalTime(&timeinfo))
  {
    String str = "---- ";
    char buffer[20]; // Buffer to hold the formatted time string
    sprintf(buffer, "%02d/%02d/%04d %02d:%02d:%02d",
            timeinfo.tm_mon + 1,     // Month, 0-based, so +1
            timeinfo.tm_mday,        // Day of the month
            timeinfo.tm_year + 1900, // Year since 1900
            timeinfo.tm_hour,        // Hour
            timeinfo.tm_min,         // Minute
            timeinfo.tm_sec);        // Second
    str += buffer;
    str += " ----";
    print_string(str, 0);
  }
  else
  {
    Serial.println("Failed to obtain time");
  }
  print_string(name, 1);
  print_string("Temperature: " + String(temp) + "°C", 2);
  print_string("Humidity: " + String(humd) + "%", 3);
  if (phValue < 2)
  {
    print_string("pH: Sensor Error!", 4);
  }
  else
  {
    print_string("pH: " + String(phValue), 4);
  }
}

void print_string(const String &str, int lineNum)
{
  Serial.println(str);
  // display.println(str);
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  // Heltec.display->setFont(ArialMT_Plain_10);
  Heltec.display->drawString(0, LINE_HEIGHT * lineNum, str);
  Heltec.display->display();
}