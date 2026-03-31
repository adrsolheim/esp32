#include "display.h"
#include <Adafruit_GFX.h>      // Core graphics library
#include <Adafruit_ST7735.h>   // ST7735 display library
#include <SPI.h>               // SPI communication library
#include <TJpg_Decoder.h>      // JPEG decoding library

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

namespace display {
    bool tft_output(int16_t x, int16_t y, uint16_t w, uint16_t h, uint16_t *bitmap) {
        if (y > tft.height() || x > tft.width()) {
            return false; // Outside screen
        }

        tft.drawRGBBitmap(x, y, bitmap, w, h);

        return true;
    }

    void init() {
        Serial.println("Initializing ST7735 display...");
        pinMode(2, OUTPUT);
        digitalWrite(2, LOW); // Turn on the built-in LED to indicate setup is running

        // Initialize display
        tft.initR(INITR_BLACKTAB); // Use INITR_BLACKTAB for most 1.8" displays
        tft.fillScreen(ST77XX_BLACK);
        
        TJpgDec.setJpgScale(1); // Set JPEG scale to 1 (no scaling)
        TJpgDec.setCallback(tft_output); // Set the callback function for JPEG output
    }


    void displayImage(const uint8_t *image, uint32_t imageSize) {
        uint32_t t = millis();

        uint16_t w = 0, h = 0;
        TJpgDec.getJpgSize(&w, &h, image, imageSize);
        Serial.println("Decoded JPEG size: " + String(w) + "x" + String(h));
        TJpgDec.drawJpg(0, 0, image, imageSize);

        Serial.println("Rendered image in " + String(millis() - t) + " ms");
    }


    // Display errors?
    void displayText(const String& text) {
        tft.fillScreen(ST77XX_BLACK);
        tft.setTextColor(ST77XX_WHITE);
        tft.setTextSize(2);
        tft.setCursor(10, 20);
        tft.println(text);
    }


}