#include "pattern.h"

void Pattern::plot(uint8_t x, uint8_t y, uint32_t c) {
  // Flip y on an odd column
  if ((x & 1) == 1)
    y = rows - y - 1;
  pixels.setPixelColor(((uint16_t) x * rows) + y, c);
}

void Pattern::plot(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b) {
  // Flip y on an odd column
  if ((x & 1) == 1)
    y = rows - y - 1;
  pixels.setPixelColor(((uint16_t) x * rows) + y, r, g, b);
}
