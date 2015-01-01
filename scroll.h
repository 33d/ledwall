#ifndef SCROLL_H_
#define SCROLL_H_

#include "pattern.h"

class Scroll: public Pattern {
  // How many levels of "sub-frames" to render
  static const int8_t sub = 8;
  int16_t pos;
public:
  Scroll(Adafruit_NeoPixel& pixels, uint8_t cols, uint8_t rows)
    : Pattern(pixels, cols, rows), pos(0) {}
  void init();
  void step();
  virtual ~Scroll() {};
};

#endif /* SCROLL_H_ */
