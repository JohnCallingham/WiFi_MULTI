#include "ArduinoJson.h"

class WiFiMultiError {


};

class WiFi_Multi {
  public:
    WiFi_Multi(const char* credentials);

    //WiFi_Multi(const char* & fred) {}

    WiFi_Multi() {}

    void addCredentials(const char* credentials) {}
    


  private:
    const char* credentials;




};

