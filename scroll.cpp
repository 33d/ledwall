#include "scroll.h"
#include <string.h>
#include <stdio.h>

#include "pattern.xbm"
#define BITMAP pattern_bits
#define WIDTH pattern_height

void Scroll::init() {
  pos = -(int16_t) cols*sub;
}

void Scroll::step() {
  delay(5);

  // How much to contribute to the first column
  // The signed modulo here is platform dependent!
  uint8_t first_val = 255-((pos % sub) * (256 / sub));
  for (uint8_t col = 0; col < cols; col++) {
    int8_t bitmapx = pos / sub + col;
    for (uint8_t y = 0, mask = 1; y < 8; y++, mask <<= 1) {
      bool first = bitmapx >= 0 && bitmapx < WIDTH && (BITMAP[bitmapx] & mask);
      bool second = bitmapx >= -1 && bitmapx < WIDTH-1 && (BITMAP[bitmapx+1] & mask);
      uint8_t val = first && !second ? first_val
        : !first && second ? (255-first_val)
        : first && second ? 255
        : 0;
      plot(col, y, val, val, val);
    }
  }

  ++pos;
  if (pos >= ((int16_t) WIDTH + cols) * sub)
    init();
}
