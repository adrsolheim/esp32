#include "display.h"
#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ST7735.h>   // ST7735 display library
#include <SPI.h>               // SPI communication library

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

namespace display {
    void init() {
        Serial.println("Initializing ST7735 display...");
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
}