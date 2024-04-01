#include <HTTPClient.h>
#include "secrets.h"

#define port 80

class HTTPWrapper
{
public:
  HTTPWrapper() {}
  ~HTTPWrapper() {}

  void testConnection();

private:
  HTTPClient http;
};