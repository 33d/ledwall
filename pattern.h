#ifndef PATTERN_H_
#define PATTERN_H_

#include "Adafruit_NeoPixel.h"
#include <stdint.h>

class Pattern {
protected:
  Adafruit_NeoPixel& pixels;
  const uint8_t rows;
  const uint8_t cols;
public:
  Pattern(Adafruit_NeoPixel& pixels, uint8_t cols, uint8_t rows)
    : pixels(pixels), rows(rows), cols(cols) {}
  virtual void init() = 0;
  virtual void step() = 0;
  virtual ~Pattern() {};
};

#endif /* PATTERN_H_ */
