#include <cJSON.h>
#include <HTTPClient.h>

#define HOST "http://autogrow-api.nrgserver.me"
#define DEFAULT_NAME "AutoGrow"
#define DEFAULT_SENSING_INTERVAL 1000 * 60 * 10 // 10 minutes
#define DEFAULT_SYNC_INTERVAL 1000 * 15         // 15 seconds

struct State
{
  std::string name;
  bool light;
  int phPollInterval;
  int dhtPollInterval;
  bool err;

  State() : name(DEFAULT_NAME), light(false), phPollInterval(DEFAULT_SENSING_INTERVAL), dhtPollInterval(DEFAULT_SENSING_INTERVAL), err(true) {}
  State(std::string name, bool light, int phPollInterval, int dhtPollInterval) : name(name), light(light), phPollInterval(phPollInterval), dhtPollInterval(dhtPollInterval), err(false) {}
};

class HTTPWrapper
{
public:
  HTTPWrapper()
  {
    http.setTimeout(5000);
  }
  ~HTTPWrapper() {}

  virtual void testConnection();
  virtual int postMeasurements(float temp, float humd, float ph, bool light);
  virtual State getState();
  virtual void postMemory();

private:
  HTTPClient http;
};