#include "heltec.h"
#include <memory>

template <typename T, typename... Args>
std::unique_ptr<T> make_unique(Args &&...args)
{
  return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

void display_values(float temp, float humd, float phValue, char *name);

void print_string(const String &str, int yHeight);