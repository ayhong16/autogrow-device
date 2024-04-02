#include "httpWrapper.h"

void HTTPWrapper::testConnection()
{
  http.begin("http://jsonplaceholder.typicode.com/todos/1"); // HTTP

  Serial.print("[HTTP] GET...\n");
  // start connection and send HTTP header
  int httpCode = http.GET();

  // httpCode will be negative on error
  if (httpCode > 0)
  {
    // HTTP header has been send and Server response header has been handled
    Serial.printf("[HTTP] GET... code: %d\n", httpCode);

    // file found at server
    if (httpCode == HTTP_CODE_OK)
    {
      String payload = http.getString();
      Serial.println(payload);
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
  http.begin(url);
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

  if (httpResponseCode > 0)
  {
    // Get the response payload
    String response = http.getString();
    Serial.print(httpResponseCode);
    Serial.print(" ");
    Serial.println(response);
  }
  else
  {
    Serial.print("Error on sending POST: ");
    Serial.println(httpResponseCode);
  }
  http.end();
  return httpResponseCode;
}