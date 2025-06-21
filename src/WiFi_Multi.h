#include "ArduinoJson.h"

class WiFi_Multi {
  public:
    WiFi_Multi(const char* credentials);

    void printCredentials();

    /**
     * Returns the matching JsonObject if ssid is in the credentials JSON.
     * Throws an invalid_argument exception if not found.
     */
    JsonObject scanNetworks();

  private:
    const char* credentials;

    JsonDocument doc;

};
