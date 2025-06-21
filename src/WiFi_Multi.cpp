#include "WiFi_Multi.h"

WiFi_Multi::WiFi_Multi(const char* credentials) {
  this->credentials = credentials;

  JsonDocument doc;

  // Deserialise the credentials JSON.
  Serial.printf("\n%6ld Deserialising credentials", millis());
  DeserializationError error = deserializeJson(doc, credentials);
  if (error) {
    Serial.printf("\n%6ld error deserialising credentials JSON: %s", millis(), error.f_str());
  } else {
    Serial.printf("\n%6ld Successfully deserialised credentials", millis());
  }
}
