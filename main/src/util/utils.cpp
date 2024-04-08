#include "both.h"
#include "utils.h"

void display_values(float temp, float humd, float phValue)
{
  // display.cls();
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