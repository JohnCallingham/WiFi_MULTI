#include "ArduinoJson.h"

class WiFi_Multi_Error {
  public:
    enum ReturnCode {
      Ok,
      DeserialisationError,
      NoWiFiNetworks,
      NoMatch
    };

    // Returns true if there is an error
    explicit operator bool() const {
      return returnCode != ReturnCode::Ok;
    }

    const char* c_str() const {
      static const char* messages[] = {"Ok", "DeserialisationError", "NoWiFiNetworks", "NoMatchingSSID"};
      return messages[returnCode];
    }

    ReturnCode returnCode;

  private:

};

class WiFi_Multi {
  public:
    /**
     * Actions;-
     *  1. Deserialises the credentials JSON file.
     *  2. Scans the available WiFi networks.
     *  3. Checks for a matching SSID between the credentials and the WiFi networks scanned.
     * If a match is found, the matching name, SSID and password are stored for later access.
     * The returned WiFi_Multi_Error object indicates success or failure.
     */
    WiFi_Multi_Error findMatchingSSID(const char* credentials);

    /**
     * Methods to access the name, SSID and password of matching SSID.
     */
    const char* getMatchingName() { return this->matchingName; }
    const char* getMatchingSSID() { return this->matchingSSID; }
    const char* getMatchingPassword() { return this->matchingPassword; }

  private:
    // Used to deserialise the credentials JSON.
    JsonDocument doc;

    // Used to return the success or failure message.
    WiFi_Multi_Error error;

    // Used to store the matching name, SSID and password.
    const char* matchingName;
    const char* matchingSSID;
    const char* matchingPassword;
};
