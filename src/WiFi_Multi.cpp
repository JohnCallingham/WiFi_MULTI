#include "WiFi_Multi.h"
#include <WiFi.h>

WiFi_Multi_Error WiFi_Multi::findMatchingSSID(const char* credentials) {
  WiFi_Multi_Error wifi_Multi_Error;

  /**
   * Deserialise the credentials JSON.
   */
  Serial.printf("\n%6ld WiFi_Multi: Deserialising credentials", millis());
  DeserializationError error = deserializeJson(doc, credentials);
  if (error) {
    Serial.printf("\n%6ld WiFi_Multi: Error deserialising credentials JSON: %s", millis(), error.f_str());
    wifi_Multi_Error.returnCode = WiFi_Multi_Error::ReturnCode::DeserialisationError;
    return wifi_Multi_Error;
  }
  Serial.printf("\n%6ld WiFi_Multi: Successfully deserialised credentials", millis());

  /**
   * Scan the WiFi networks.
   */
  Serial.printf("\n%6ld WiFi_Multi: Scanning WiFi networks", millis());

  WiFi.mode(WIFI_STA);

  int n = WiFi.scanNetworks();

  if (n==0) {
    Serial.printf("\n%6ld WiFi_Multi: No WiFi networks found", millis());
    wifi_Multi_Error.returnCode = WiFi_Multi_Error::ReturnCode::NoWiFiNetworks;
    return wifi_Multi_Error;
  }
  Serial.printf("\n%6ld WiFi_Multi: Successfully scanned WiFi networks", millis());

  /**
   * Check for an SSID found in the scan which we have a match for in the credentials.
   */
  Serial.printf("\n%6ld WiFi_Multi: Checking for matching SSID", millis());

  // Step through the credentials as the outer loop so that APs higher up in the credentials list get priority.
  for (JsonObject elem : doc.as<JsonArray>()) {
    for (uint8_t i=0; i<n; i++) {
      if (strcmp(WiFi.SSID(i).c_str(), elem["ssid"]) == 0) {
        Serial.printf("\n%6ld WiFi_Multi: Matching SSID found: %s", millis(), WiFi.SSID(i).c_str());
        // If a match has been found, then store the matching name,
        //  SSID and password so it can be accessed later.
        this->matchingName = elem["name"];
        this->matchingSSID = elem["ssid"];
        this->matchingPassword = elem["password"];

        wifi_Multi_Error.returnCode = WiFi_Multi_Error::ReturnCode::Ok;
        return wifi_Multi_Error;
      }
    }
  }

  // for (uint8_t i=0; i<n; i++) {
  //   for (JsonObject elem : doc.as<JsonArray>()) {
  //     if (strcmp(WiFi.SSID(i).c_str(), elem["ssid"]) == 0) {
  //       Serial.printf("\n%6ld WiFi_Multi: Matching SSID found: %s", millis(), WiFi.SSID(i).c_str());
  //       // If a match has been found, then store the matching name,
  //       //  SSID and password so it can be accessed later.
  //       this->matchingName = elem["name"];
  //       this->matchingSSID = elem["ssid"];
  //       this->matchingPassword = elem["password"];

  //       wifi_Multi_Error.returnCode = WiFi_Multi_Error::ReturnCode::Ok;
  //       return wifi_Multi_Error;
  //     }
  //   }
  // }

  // No match was found, so set returnCode accordingly and return.
  wifi_Multi_Error.returnCode = WiFi_Multi_Error::ReturnCode::NoMatch;
  return wifi_Multi_Error;
}
