#include <cJSON.h>
#include <HTTPClient.h>

#define url "http://ec2-107-23-54-207.compute-1.amazonaws.com:5000/sensor_data"

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