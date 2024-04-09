#include <cJSON.h>
#include <HTTPClient.h>

#define url "http://autogrow.nrgserver.me/sensor_data"

class HTTPWrapper
{
public:
  HTTPWrapper() {}
  ~HTTPWrapper() {}

  virtual void testConnection();
  virtual int postMeasurements(float temp, float humd, float ph, bool light);

private:
  HTTPClient http;
};