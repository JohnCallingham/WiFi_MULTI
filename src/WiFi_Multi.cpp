#include "WiFi_Multi.h"
#include <stdexcept>
using namespace std;
#include <WiFi.h>

WiFi_Multi::WiFi_Multi(const char* credentials) {
  this->credentials = credentials;
 
  // Deserialise the credentials JSON.
  Serial.printf("\n%6ld Deserialising credentials", millis());
  DeserializationError error = deserializeJson(doc, credentials);
  if (error) {
    Serial.printf("\n%6ld error deserialising credentials JSON: %s", millis(), error.f_str());
    // TO DO: throw an exception here.
  } else {
    Serial.printf("\n%6ld Successfully deserialised credentials", millis());
  }
}

JsonObject WiFi_Multi::scanNetworks() {
  WiFi.mode(WIFI_STA);

  int n = WiFi.scanNetworks();

  if (n==0) {
    Serial.printf("\n%6ld No WiFi networks found", millis());
    // TO DO: throw an exception here.
  }

  for (uint8_t i=0; i<n; i++) {
    for (JsonObject elem : doc.as<JsonArray>()) {
      if (strcmp(WiFi.SSID(i).c_str(), elem["ssid"]) == 0) {
        return elem;
      }
    }
  }
  throw invalid_argument("no matching SSID found in credentials");
}

void WiFi_Multi::printCredentials() {
  const char *name;

  for (JsonObject elem : doc.as<JsonArray>()) {
    name = elem["name"];
    Serial.printf("\nWiFi_Multi name: %s", name);
  }
}
