#pragma once

#include <stdint.h>

// Define pins used for the ST7735
#define TFT_CS     10
#define TFT_DC      9
#define TFT_RST     8

namespace display {
    void init();
    void displayImage(const uint8_t *image, uint32_t imageSize);
}