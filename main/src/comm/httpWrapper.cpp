#include "httpWrapper.h"

void HTTPWrapper::testConnection()
{
  http.begin("http://jsonplaceholder.typicode.com/todos/1"); // HTTP

  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      Serial.println("HTTP connection successful");
    }
  }
  else
  {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

int HTTPWrapper::postMeasurements(float temp, float humd, float ph, bool light)
{
  http.begin(HOST, 80, "/api/reading");
  http.addHeader("Content-Type", "application/json");
  cJSON *root = cJSON_CreateObject();

  std::string light_string;
  if (light)
  {
    light_string = "true";
  }
  else
  {
    light_string = "false";
  }

  // Add data to the JSON object
  cJSON_AddNumberToObject(root, "temp", temp);
  cJSON_AddNumberToObject(root, "humd", humd);
  cJSON_AddNumberToObject(root, "ph", ph);
  cJSON_AddStringToObject(root, "light", light_string.c_str());

  char *postData = cJSON_Print(root);

  int httpResponseCode = http.POST(postData);

  if (httpResponseCode <= 0)
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return httpResponseCode;
}

State HTTPWrapper::getState()
{
  http.begin(HOST, 80, "/api/state");
  http.addHeader("Content-Type", "application/json");

  int httpResponseCode = http.GET();

  Serial.println(httpResponseCode);

  if (httpResponseCode != HTTP_CODE_OK)
  {
    Serial.print("Error on sending GET: ");
    Serial.println(httpResponseCode);
    return State();
  }
  cJSON *root = cJSON_Parse(http.getString().c_str());
  cJSON *name = cJSON_GetObjectItem(root, "name");
  cJSON *light = cJSON_GetObjectItem(root, "light");
  cJSON *phPollInterval = cJSON_GetObjectItem(root, "phPollInterval");
  cJSON *dhtPollInterval = cJSON_GetObjectItem(root, "dhtPollInterval");

  State state(cJSON_GetStringValue(name), cJSON_IsTrue(light), cJSON_GetNumberValue(phPollInterval), cJSON_GetNumberValue(dhtPollInterval));
  cJSON_Delete(root);
  http.end();
  return state;
}