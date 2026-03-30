#pragma once

bool loadWiFiCredentialsFromNVS(std::string* ssid, std::string* password);
bool saveWiFiCredentialsToNVS(std::string ssid, std::string password);
bool setupWiFi();