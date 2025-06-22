#include "ArduinoJson.h"

class WiFi_Multi_Error {
  public:

    // Returns true if there is an error
    explicit operator bool() const {
      //return code_ != Ok;
      return false;
  }

  private:


};

class WiFi_Multi {
  public:
    WiFi_Multi(const char* credentials);
    WiFi_Multi() {};

    WiFi_Multi_Error findMatchingSSID(const char* credentials);

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
