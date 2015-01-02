#ifndef PATTERN_H_
#define PATTERN_H_

#include "Adafruit_NeoPixel.h"
#include <stdint.h>

class Pattern {
protected:
  Adafruit_NeoPixel& pixels;
  const uint8_t rows;
  const uint8_t cols;
  void plot(uint8_t x, uint8_t y, uint32_t c);
  void plot(uint8_t x, uint8_t y, uint8_t r, uint8_t g, uint8_t b);
public:
  Pattern(Adafruit_NeoPixel& pixels, uint8_t cols, uint8_t rows)
    : pixels(pixels), rows(rows), cols(cols) {}
  virtual void init() = 0;
  virtual bool step() = 0;
  virtual ~Pattern() {};
};

#endif /* PATTERN_H_ */
