#include <WiFi.h>
#include <Preferences.h>

#if __has_include(<secrets.h>)
    #include "secrets.h"
    #define SECRETS_H_EXISTS 1
#else
    #define SECRETS_H_EXISTS 0
#endif

namespace {
    Preferences prefs;

    bool loadWiFiCredentialsFromNVS(std::string* ssid, std::string* password) {
        prefs.begin("wifi", false); // read/write mode because "wifi" might not exist yet
        *ssid = prefs.getString("ssid", "").c_str();
        *password = prefs.getString("pass", "").c_str();
        prefs.end();

        return !ssid->empty();
    }
    bool saveWiFiCredentialsToNVS(std::string ssid, std::string password) {
        if (ssid.empty()  || password.empty()) {
            return false;
        }
        prefs.begin("wifi", false);
        prefs.putString("ssid", ssid.c_str());
        prefs.putString("pass", password.c_str());
        prefs.end();

        return true;
    }
}

bool setupWiFi() {
    WiFi.mode(WIFI_STA);
    std::string ssid;
    std::string pass;
    if (!loadWiFiCredentialsFromNVS(&ssid, &pass)) {
        #if SECRETS_H_EXISTS
            boolean wifiSaved = saveWiFiCredentialsToNVS(WIFI_SSID, WIFI_PASSWORD);
            if (!wifiSaved) {
                Serial.println("Failed to save WiFi credentials to NVS");
                return false;
            }
            boolean wifiLoaded = loadWiFiCredentialsFromNVS(&ssid, &pass);
            if (!wifiLoaded) {
                Serial.println("Failed to load WiFi credentials from NVS...");
                return false;
            }
        #else
            Serial.println("Missing WiFi credentials...");
            return false;
        #endif
    }

    WiFi.begin(ssid.c_str(), pass.c_str());
    unsigned long start = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - start < 30000) {
        Serial.println("Trying to connect to WiFi...");
        delay(3000);
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.println("Failed to connect to WiFi...");
        return false;
    }

    Serial.printf("\nConnected to %s\n", WiFi.SSID().c_str());
    return true;
}