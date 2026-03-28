#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>


#define TFT_CS         10
#define TFT_RST        8
#define TFT_DC         9
#define TFT_MOSI       11
#define TFT_MISO       13
#define SerialDebugging true


Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  pinMode(10, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(10, HIGH);  // change state of the LED by setting the pin to the HIGH voltage level
  delay(1000);                      // wait for a second
digitalWrite(10, LOW);   // change state of the LED by setting the pin to the LOW voltage level
  delay(1000);   
}