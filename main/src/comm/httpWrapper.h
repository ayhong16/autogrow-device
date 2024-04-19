#include <cJSON.h>
#include <HTTPClient.h>

#define HOST "http://autogrow.nrgserver.me"
#define DEFAULT_NAME "AutoGrow"
#define DEFAULT_SENSING_INTERVAL 1000 * 60 * 20 // 20 minutes
#define DEFAULT_SYNC_INTERVAL 1000 * 10         // 10 seconds

struct State
{
  std::string name;
  bool light;
  int phPollInterval;
  int dhtPollInterval;

  State() : name(DEFAULT_NAME), light(false), phPollInterval(DEFAULT_SENSING_INTERVAL), dhtPollInterval(DEFAULT_SENSING_INTERVAL) {}
  State(std::string name, bool light, int phPollInterval, int dhtPollInterval) : name(name), light(light), phPollInterval(phPollInterval), dhtPollInterval(dhtPollInterval) {}
};

class HTTPWrapper
{
public:
  HTTPWrapper() {}
  ~HTTPWrapper() {}

  virtual void testConnection();
  virtual int postMeasurements(float temp, float humd, float ph, bool light);
  virtual State getState();

private:
  HTTPClient http;
};