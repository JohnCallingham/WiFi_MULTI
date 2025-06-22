/**
 * Wifi_Multi
 * A way to allow an esp32 to automatically connect to different WiFi APs depending on location. 
 * Keep a JSON format file credentials.h with name, ssid and password combinations.
 * On start up;-
 *  1. Do a WiFi scan and return all SSIDs in range.
 *  2. Check the JSON credentials file to see if any SSID in range is in the file.
 *  3. If so, use its password to connect.
 * Format of credentials.h;-
 * const char* credentials = R"===(
 * [
 *   {
 *     "name":"FirstAP",
 *     "ssid":"FirstSSID",
 *     "password":"FirstPassword"
 *   },
 *   {
 *     "name":"SecondAP",
 *     "ssid":"SecondSSID",
 *     "password":"SecondPassword"
 *   },
 *   {
 *     "name":"ThirdAP",
 *     "ssid":"ThirdSSID",
 *     "password":"ThirdPassword"
 *   }
 * ]
 * )===";
 */
#include <Arduino.h>
#include <WiFi.h>
#include "WiFi_Multi.h"
#include "credentials.h"

WiFi_Multi wifi_Multi;

void setup() {
  Serial.begin(115200);

  delay(5000);

  Serial.printf("\n%6ld Started program", millis());

  WiFi_Multi_Error error = wifi_Multi.findMatchingSSID(credentials);
  if (error) {
    // Display error and exit program.
    Serial.printf("\n%6ld Error finding matching SSID: %s", millis(), error.c_str());
  } else {
    // Match found. Use wifi_Multi.SSID and wifi_Multi.password to connect to the matching SSID.
    const char* name = wifi_Multi.getMatchingName();
    const char* ssid = wifi_Multi.getMatchingSSID();
    const char* password = wifi_Multi.getMatchingPassword();

    WiFi.setMinSecurity(WIFI_AUTH_WPA_PSK); // Default is WPA2

    if( WiFi.status() != WL_CONNECTED ) {
      Serial.printf("\n%6ld Starting connection to %s SSID: %s", millis(), name, ssid);

      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(2000); // Originally 1000mS, but a second ESP32 didn't work until changed to 2000mS.
        Serial.printf("\n%6ld Connecting to %s SSID: %s", millis(), name, ssid);
      }
      Serial.printf("\n%6ld Connected to %s SSID: %s", millis(), name, ssid);
      Serial.printf("\n%6ld IP address: %s", millis(), WiFi.localIP().toString());
    }
  }
}

void loop() {
}
