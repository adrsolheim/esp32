#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ST7735.h>   // ST7735 display library
#include <SPI.h>               // SPI communication library
#include "esp_wifi.h"
#include "connect_wifi.h"
#include "httpserver.h"
#include "display.h"

void setup() {
  Serial.begin(115200); // ESP32 baud rate
  delay(10000);         // Make time for Serial Monitor to connect to inspect output

  wifi::connect();
  httpserver::init();
  display::init();
}

void loop() {
  httpserver::listenForConnections();
}