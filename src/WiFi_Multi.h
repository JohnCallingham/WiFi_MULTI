#include "ArduinoJson.h"

class WiFi_Multi_Error {
  public:
    enum errorCode {
      Ok,
      DeserialisationError,
      NoWiFiNetworks,
      NoMatch,
      WiFiError //used ??
    };

    // Returns true if there is an error
    explicit operator bool() const {
      return code != errorCode::Ok;
      //return false;
  }

    errorCode code;

  private:
    //errorCode code;

};

class WiFi_Multi {
  public:
    //WiFi_Multi(const char* credentials);
    WiFi_Multi() {};

    WiFi_Multi_Error findMatchingSSID(const char* credentials);

    const char* getFoundName() { return this->foundName; }
    const char* getFoundSSID() { return this->foundSSID; }
    const char* getFoundPassword() { return this->foundPassword; }


    //void printCredentials();

    /**
     * Returns the matching JsonObject if ssid is in the credentials JSON.
     * Throws an invalid_argument exception if not found.
     */
    //JsonObject scanNetworks();

  private:
    const char* credentials;

    JsonDocument doc;
  
    WiFi_Multi_Error error;

    const char* foundName;
    const char* foundSSID;
    const char* foundPassword;

};
