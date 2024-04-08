#include "Both.h"

Both both(Serial, *Heltec.display);

// Constructor implementation
Both::Both(Print &_serial, Print &_display) : serial(_serial), display(_display) {}

// Override the write method from the Print class for uint8_t
size_t Both::write(uint8_t c)
{
  serial.write(c);         // Write to the serial monitor
  return display.write(c); // Write to the display
}

// Override the write method from the Print class for const uint8_t*
size_t Both::write(const uint8_t *buffer, size_t size)
{
  serial.write(buffer, size);         // Write to the serial monitor
  return display.write(buffer, size); // Write to the display
}

// Additional methods for printing to both the serial monitor and the display
void Both::println(const String &str)
{
  serial.println(str);
  display.println(str);
}