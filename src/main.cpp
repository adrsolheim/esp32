#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ST7735.h>   // ST7735 display library
#include <SPI.h>               // SPI communication library
#include "esp_wifi.h"
#include "connect_wifi.h"

// Define pins used for the ST7735
#define TFT_CS     10
#define TFT_DC      9
#define TFT_RST     8

// Create the display object
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  // Initialize Serial Monitor
  Serial.begin(115200); // ESP32 baud rate
  delay(30000); // Make time for Serial Monitor to connect to inspect output
  Serial.println("Initializing ST7735 display...");

  setupWiFi();
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW); // Turn on the built-in LED to indicate setup is running

  // Initialize display
  tft.initR(INITR_BLACKTAB); // Use INITR_BLACKTAB for most 1.8" displays
  tft.fillScreen(ST77XX_BLACK);
  
  // Display test text
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(10, 20);
  tft.println("ST7735 Test på fest!");
}

void loop() {
  Serial.println("Looping...");
  delay(1000);
}