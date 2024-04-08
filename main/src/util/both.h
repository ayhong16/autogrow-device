#ifndef BOTH_H
#define BOTH_H

#include <Arduino.h>
#include "heltec.h"
#include <Print.h>

class Both : public Print
{
public:
  // Constructor takes two Print references
  Both(Print &_serial, Print &_display);

  // Override the write method from the Print class for uint8_t
  size_t write(uint8_t c) override;

  // Override the write method from the Print class for const uint8_t*
  size_t write(const uint8_t *buffer, size_t size) override;

  // Additional methods for printing to both the serial monitor and the display
  void println(const String &str);

private:
  Print &serial;  // Reference to the serial monitor
  Print &display; // Reference to the display
};

extern Both both;

#endif // BOTH_H
