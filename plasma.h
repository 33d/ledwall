#ifndef PLASMA_H_
#define PLASMA_H_

#include "pattern.h"

class Plasma: public Pattern {
  uint8_t pos1, pos2, pos3, pos4;
public:
  Plasma(Adafruit_NeoPixel& pixels, uint8_t cols, uint8_t rows)
    : Pattern(pixels, cols, rows), pos1(0), pos2(0), pos3(0), pos4(0) {}
  void init();
  bool step();
  virtual ~Plasma() {};
};

#endif /* MATRIX_H_ */
